/*
Program written by Jacob Howell
December, 2021
Module: ELEC 347
Task 4: Real Time Implementation of parametric EQ
*/

#ifndef __LED_H
#define __LED_H
#ifdef __cplusplus
extern "C" {
#endif
	
#include "stm32f4xx.h"
#include "Delay.h"
//#include "buzzer.h"
#define OFF 0			//create off constant to make code more readable
#define ON 1			//create on constant to make code more readable

#define LD1 0
#define LD2 7
#define LD3 14


//assign LED pin numbers
#define TRAF_RED1 2		
#define TRAF_YEL1 3
#define TRAF_GEN1 6
#define TRAF_RED2 7
#define TRAF_YEL2 8
#define TRAF_GEN2 9
#define WHITE_LED 10


#define LDR 0

void Init_LEDs(void);
void Init_Traffic_LEDs(void);


void Toggle_B(int PIN);
void Toggle_C(int PIN);

void Set_B(int B_PIN, int state);
void Set_C(int C_PIN, int state);
void readySteadyGo();
void morseCodeScore(unsigned int score);
void lightController(int R1, int Y1, int G1, int GM, int R2, int Y2, int G2);

void morse_dot();
void morse_dash();


#ifdef __cplusplus
}
#endif

#endif
