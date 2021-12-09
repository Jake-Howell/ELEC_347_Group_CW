
#include "lcd.h"
#include "Delay.h"
//void lcd_delayus(unsigned int us)		//blocking delay for LCD, argument is approximate number of micro-seconds to delay
//{
//	unsigned char i;
//	while(us--)
//	{
//		for(i=0; i<SystemCoreClock/4000000; i++){__NOP();}
//	}
//}

void WaitLcdBusy(void)
{
//	Wait3_us(3000);				//3ms blocking delay
	
	set_LCD_bus_input();
	set_LCD_RW();						//set to read
	clr_LCD_RS();						//Register Select (comand/data)
	int busyPin;						
	
	do{
		set_LCD_E();																	//set enable
		Wait3_us(20);																	//hold enable high
		busyPin = LCD_PORT->IDR & (1u <<	BUSY_FLAG);	//update port
		Wait3_us(20);
		clr_LCD_E();																	//reset enable
		LCD_strobe();
		//Wait3_us(10);		
	}while(busyPin != 0);
	Wait3_us(20);
	set_LCD_bus_output();
	Wait3_us(20);
}

void set_LCD_data(unsigned char data)
{
	unsigned char nibble1 = (data & 0xF0);
	unsigned char nibble2 = ((data<<0x4) & 0xF0);
	
	LCD_PORT->BSRR = 0x00FF0000;						//clear data bus
	LCD_PORT->BSRR = nibble1;								//only send first 4 bits of data
	LCD_strobe();														//apply first 4 bits of data
	
	LCD_PORT->BSRR = 0x00FF0000;						//clear data bus
	LCD_PORT->BSRR = nibble2;								//only send second 4 bits of data
	LCD_strobe();														//apply second 4 bits of data

}

void LCD_strobe(void)		//10us high pulse on LCD enable line
{
	Wait3_us(10);
	set_LCD_E();
	Wait3_us(10);
	clr_LCD_E();
}


void cmdLCD(unsigned char cmd)		//sends a byte to the LCD control register
{
	WaitLcdBusy();				//wait for LCD to be not busy
	
	clr_LCD_RS();					//control command
	clr_LCD_RW();					//write command
	set_LCD_data(cmd);		//set data on bus
	
}


void putLCD(unsigned char put)	//sends a char to the LCD display
{
	
	WaitLcdBusy();				//wait for LCD to be not busy
	
	set_LCD_RS();					//data command
	clr_LCD_RW();					//write command
	set_LCD_data(put);		//set data on bus
}

void lcdLocate(int row, int col){
	
	if (row == 0){cmdLCD(LCD_LINE1+col);}			//select location in LCD
	else if (row == 1){cmdLCD(LCD_LINE2+col);}	//memory to write data
}

void init_LCD(void)
{
		SystemCoreClockUpdate();
		Wait3_ms(40);												//40ms delay to allow VDD to rise to 4.5V
		RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;	//enable LCD port clock
	
	
			//CONFIG LCD GPIO PINS
		LCD_PORT->MODER&=~(						//clear pin direction settings
			(3u<<(2*LCD_RS_pin))				//reset Reg Select
			|(3u<<(2*LCD_RW_pin))				//reset Read/Write
			|(3u<<(2*LCD_E_pin))				//reset Enable
			|(0xFFFF<<(2*LCD_D0_pin))		//D4 - D7	reset
			|3u<<(2*LCD_BACKLIGHT)
			);
	
	
	LCD_PORT->MODER|=(							//reset pin direction settings to digital outputs
			(1u<<(2*LCD_RS_pin))				//Reg Select set to output mode
			|(1u<<(2*LCD_RW_pin))				//Read/Write set to output mode
			|(1u<<(2*LCD_E_pin))				//Enable set to output mode
			|(0x5555<<(2*LCD_D0_pin))	  //D4-D7 set to output mode D0-D3 output too (for grounding reasons)
			|1u<<(2*LCD_BACKLIGHT)			//enable backlight pin
		);
		
	//reset all pin output type values	
	LCD_PORT->OTYPER &= ~(
	(1<<(LCD_D0_pin))
	|(1<<(LCD_D1_pin))
	|(1<<(LCD_D2_pin))
	|(1<<(LCD_D3_pin))
	|(1<<(LCD_D4_pin))
	|(1<<(LCD_D5_pin))
	|(1<<(LCD_D6_pin))
	|(1<<(LCD_D7_pin))
	);
	//SET to open drain
	LCD_PORT->OTYPER |= (
	(1<<(LCD_D0_pin))
	|(1<<(LCD_D1_pin))
	|(1<<(LCD_D2_pin))
	|(1<<(LCD_D3_pin))
	|(1<<(LCD_D4_pin))
	|(1<<(LCD_D5_pin))
	|(1<<(LCD_D6_pin))
	|(1<<(LCD_D7_pin))
	);
	
	LCD_PORT->PUPDR &= ~(						//clear pin direction settings
			(3u<<(2*LCD_RS_pin))				//reset Reg Select
			|(3u<<(2*LCD_RW_pin))				//reset Read/Write
			|(3u<<(2*LCD_E_pin))				//reset Enable
			|(0xFFFF<<(2*LCD_D0_pin))		//D4 - D7	reset
			);
	LCD_PORT->PUPDR |=	 						//clear pin direction settings
			(2u<<(2*LCD_RS_pin))				//reset Reg Select
			|(2u<<(2*LCD_RW_pin))				//reset Read/Write
			|(2u<<(2*LCD_E_pin))				//reset Enable
			|(0xAAAA<<(2*LCD_D0_pin));	//D4 - D7	reset
	




	
	//LCD INIT COMMANDS
	clr_LCD_RS();					//all lines default low
	clr_LCD_RW();
	clr_LCD_E();
	set_BackLight();
	
	Wait3_ms(40);											//40ms delay to allow VDD to rise to 4.5V
	LCD_PORT->BSRR = 0x00FF0030;			//Function set: 8-Bit
	LCD_strobe();											//apply instruction
	
	Wait3_us(40);											//40us delay
	LCD_PORT->BSRR = 0x00FF0028;			//Function set: Set to 4-bit
	LCD_strobe();											//apply instruction
	
	Wait3_us(40);											//40us delay
	LCD_PORT->BSRR = 0x00FF0028;			//Function set: Set to 4-bit (instruction)
	LCD_strobe();											//apply instruction
	
	Wait3_ms(1);											//1ms delay
	
	//now normal comands can be used
	
	
	cmdLCD(0x28);	//Function set: 2 line, 4-bit, 5x8 dots
	cmdLCD(0x0C);	//Display on, Cursor blinking command
	cmdLCD(0x01);	//Clear LCD
	Wait3_ms(2);
	cmdLCD(0x06);	//Entry mode, auto increment with no shift
}

void updateLCD(char line[LCD_WIDTH],int LineNo){
	
	char printedLine[LCD_WIDTH] = "                ";//16 clear spaces to fill rest of screen

	for (int n = 0;  n < LCD_WIDTH; n++){
		
		if (line[n] == 0){n = LCD_WIDTH;}				//check for null byte
		else {printedLine[n] = line[n];}				//swap char
		
	}
	
	lcdLocate(LineNo,0);											//select printing position
	for (int i = 0; i < LCD_WIDTH; i++){			//itterate through all 16 chars
				putLCD(printedLine[i]);							//print string
	}
	lcdLocate(0,0);														//reset location
}

