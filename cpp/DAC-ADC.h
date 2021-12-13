/*
Program written by Jacob Howell
December, 2021
Module: ELEC 347
Task 4: Real Time Implementation of parametric EQ
*/

#ifndef _DAC_ADC_H
#define _DAC_ADC_H
#ifdef __cplusplus
extern "C" {
#endif
	
#include <stm32f4xx.h>
#include "math.h"		


class AnalogOut{
	
	public:
		AnalogOut(char port, unsigned short pin);
		void output(unsigned short data);
	
	private:
		void init_DAC(void);
		char port;
		unsigned short pin;
	
};

class AnalogIn{
	
	public:
		AnalogIn(char port, unsigned short pin, unsigned short chanel);
		unsigned short read(void);
	
	private:
		void init_ADC(void);								//initalise ADC
		char port;
		unsigned short pin;
		unsigned short chanel;
	
	
};
#ifdef __cplusplus
}
#endif
#endif
