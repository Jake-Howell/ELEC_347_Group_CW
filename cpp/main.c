#include 	<stm32f4xx.h>
#include 	"Delay.h"
#include 	"lcd.h"
#include 	"LED.h"
#include	"usart.h"
#include 	"DAC-ADC.h"
#include	"filter.h"
#include 	"PLL_Config.c"
#ifdef __cplusplus
extern "C" {
#endif


#define BUFF_SIZE 6
#define SAMP_FREQ 96000
#define CEN_FREQ	10000
#define Q_FAC			5
#define BOOST			3

unsigned int newSampleFlag;
char usart_char;

AnalogIn 		mic('A', 6, 6);		//port, pin, chanel // MP3 Right
//AnalogIn 		mic('A', 3, 3);		//mic teat
AnalogOut 	speaker('A', 5);	//port, pin
Filter bell(SAMP_FREQ, CEN_FREQ, Q_FAC, BOOST);

int main(){
	PLL_Config();
	SystemCoreClockUpdate();
	
	__disable_irq();
	
	Init_LEDs();
	//timer 2 used for 96KHz sample rate
	Init_Timer2(9, 107, ENABLE_ISR);
	//timer 3 is used for creating delays and ticks every us
	Init_Timer3(PSC_Var_Delay, ARR_Var_Delay, DISABLE_ISR);

	
	init_LCD();									//initalise LCD in 4bit mode
	init_USART(115200);					//initalise USART with 115200 baud rate, 1 stop bit, even parity
	

	
	__enable_irq();							//after all initalisation, turn on interupts
	
	
	char stringBuff[80];
	unsigned short input_x = 0, output_y = 0;
	coeffs_t c = bell.getCoeffs();
	sprintf(stringBuff, "\r\na1: %4.2f  a2: %4.2f a3: %4.2f\r\nb1: %4.2f b2: %4.2f b3: %4.2f\r\n",c.a[0],c.a[1],c.a[2],c.b[0], c.b[1],c.b[2]);
	updateLCD("Real Time EQ :)",0);
	usart_print(stringBuff);
	coeffs_t cNew = {{1.0f, -1.3781f, 0.7370f},{1.0542f, -1.3781f, 0.6828f}};
	
	bell.setCoeffs(cNew);
	
	c = bell.getCoeffs();
	sprintf(stringBuff, "\r\nNEW\r\na1: %4.2f  a2: %4.2f a3: %4.2f\r\nb1: %4.2f b2: %4.2f b3: %4.2f\r\n",c.a[0],c.a[1],c.a[2],c.b[0], c.b[1],c.b[2]);
	usart_print(stringBuff);
	
	
	while(1){
		
		while (newSampleFlag == 1){
			//Set_C(2,0);
			input_x = mic.read();
//			head = (head + 1)%BUFF_SIZE;
			
			output_y = bell.FilterStream(input_x);
			
			speaker.output(output_y);
//			tail = (tail + 1)%BUFF_SIZE;
			
			newSampleFlag = 0;
		}
		//Set_C(2,1);
		
		
		
		//Wait3_ms(5);
//		
		//out = buffer[tail];
		
//		sprintf(stringBuff,"X: %d\tY: %d\n\r", input_x, output_y);
//		usart_print(stringBuff);
		
		
		

	}
}

#ifdef __cplusplus
}
#endif

