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
float coeffs_A[3] = {1.0f, -1.8657f, 0.8747f};		//define A coeffs
float coeffs_B[3] = {0.9436f, -1.8657f, 0.9311f};	//define B coeffs

//AnalogIn 		Ain_L('B', 0, 8);		//port, pin, chanel //select input
//AnalogIn		Ain_R('B', 1, 9);

//AnalogOut 	speaker_L('A', 4);	//port, pin					//select output
//AnalogOut		speaker_R('A', 5);
//Filter bell_L(coeffs_A, coeffs_B);		//create filter object
//Filter bell_R(coeffs_A, coeffs_B);		//create filter object
	
AnalogIn mic('A', 6, 6);
AnalogOut speaker('A', 5);
Filter bell(coeffs_A, coeffs_B);		//create filter object

int main(){
	PLL_Config();																//set clock to 180MHz
	SystemCoreClockUpdate();
	
	__disable_irq();
	
	
	Init_Timer2(9, 107, ENABLE_ISR);						//timer 2 used for 96KHz sample rate
	Init_Timer3(PSC_Var_Delay, ARR_Var_Delay, DISABLE_ISR);	//timer 3 used for blocking delays for initalisations
	init_LCD();																	//initalise LCD in 4bit mode

	__enable_irq();															//after initalisation, turn on interupts
	
	unsigned short input_x = 0, output_y = 0;
	updateLCD("ELEC 347",0);										//print message to display
	updateLCD("Real Time EQ",1);

	
	
	while(1){
		
		while (newSampleFlag == 1){								//Wait for interupt flag
			input_x 	= mic.read()-2048;						//get next input from ADC
			output_y 	= bell.FilterStream(input_x);	//pass input through filter (multiple filters can be cascaded)
			speaker.output(output_y+2048);					//send output to DAC
//			speaker_L.output(bell_L.FilterStream(Ain_L.read()-2048)+2047);
//			speaker_R.output(bell_R.FilterStream(Ain_R.read()-2048)+2047);
			
			newSampleFlag = 0;											//set sample flag to 0 and exit loop
		}
		__NOP();																	//Do nothing
	}
}

#ifdef __cplusplus
}
#endif

