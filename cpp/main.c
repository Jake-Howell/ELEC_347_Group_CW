/*
Program written by Jacob Howell
December, 2021
Module: ELEC 347
Task 4: Real Time Implementation of parametric EQ
*/

#include 	<stm32f4xx.h>
#include 	"Delay.h"
#include 	"lcd.h"
#include 	"DAC-ADC.h"
#include	"filter.h"
#include 	"PLL_Config.c"
#ifdef __cplusplus
extern "C" {
#endif


#define BUFF_SIZE 6
#define SAMP_FREQ 96000
#define CEN_FREQ	1500
#define Q_FAC			4
#define BOOST			-4

unsigned int newSampleFlag;


AnalogIn 		mic('A', 6, 6);		//port, pin, chanel //select input
AnalogOut 	speaker('A', 5);	//port, pin					//select output
Filter bell(SAMP_FREQ, CEN_FREQ, Q_FAC, BOOST);		//create filter object

int main(){
	PLL_Config();																//set clock to 180MHz
	SystemCoreClockUpdate();
	
	__disable_irq();
	
	
	Init_Timer2(9, 107, ENABLE_ISR);						//timer 2 used for 96KHz sample rate
	init_LCD();																	//initalise LCD in 4bit mode

	__enable_irq();															//after initalisation, turn on interupts
	
	unsigned short input_x = 0, output_y = 0;
	updateLCD("ELEC 347",0);										//print message to display
	updateLCD("Real Time EQ",1);

	
	
	while(1){
		
		while (newSampleFlag == 1){								//Wait for interupt flag
			input_x 	= mic.read()-2048;						//get next input from ADC
			output_y 	= bell.FilterStream(input_x);	//pass input through filter (multiple filters can be cascaded)
			speaker.output(output_y+2047);					//send output to DAC
			
			newSampleFlag = 0;											//set sample flag to 0 and exit loop
		}
		__NOP();																	//Do nothing
	}
}

#ifdef __cplusplus
}
#endif

