/*
Program written by Jacob Howell
December, 2021
Module: ELEC 347
Task 4: Real Time Implementation of parametric EQ
*/

#include "LED.h"

void Init_LEDs(void){
	//ENABLE PORT(S)
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;	//ONLY GPIO B clock enable
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;	//ONLY GPIO C clock enable
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;	//ONLY GPIO F clock enable
	
	//CONFIGURE PORT PIN FUNCTIONS
	//enable LD1 LD2 LD3 as outputs(PB0, PB7, PB14)
	GPIOB->MODER |= (1<<(2*LD1))|(1<<(2*LD2))|(1<<(2*LD3));										
	GPIOB->MODER &= ~((0x2<<(0x2*LD1))|(0x2<<(0x2*LD2))|(0x2<<(0x2*LD3)));


	//CONFIGURE PORT PIN FUNCTIONS
	//enable TRAFF LEDs as outputs (PC2, PC3, PC6, PC7, PC8, PC9)
	//TRAFF_1
	GPIOC->MODER |= (1<<(2*TRAF_RED1))|(1<<(2*TRAF_YEL1))|(1<<(2*TRAF_GEN1));
	GPIOC->MODER &= ~((2<<(2*TRAF_RED1))|(2<<(2*TRAF_YEL1))|(2<<(2*TRAF_GEN1)));
	
	//TRAFF_2
	GPIOC->MODER |= (1<<(2*TRAF_RED2))|(1<<(2*TRAF_YEL2))|(1<<(2*TRAF_GEN2));	
	GPIOC->MODER &= ~((2<<(2*TRAF_RED2))|(2<<(2*TRAF_YEL2))|(2<<(2*TRAF_GEN2)));
	
	//WHITE_LED
	GPIOF->MODER |= (1<<(2*WHITE_LED));
	GPIOF->MODER &= ~(2<<(2*WHITE_LED));
	
	//this register only uses 16 bits (1 bit per pin)
	//set to PUSH/PULL (reset state)
	GPIOC->OTYPER &= ~((1<<(TRAF_RED1))|(1<<(TRAF_YEL1))|(1<<(TRAF_GEN1)));
	//SET to open drain(set state)
	GPIOC->OTYPER |= ((1<<(TRAF_RED2))|(1<<(TRAF_YEL2))|(1<<(TRAF_GEN2)));
	GPIOF->OTYPER |= (1<<WHITE_LED);
	//set Initial values to turn off LEDs
	GPIOC->BSRR = 0x004C0380;
	GPIOF->ODR |= (1<<WHITE_LED);
}


void Toggle_B(int B_PIN){
	GPIOB->ODR^=(1u<<B_PIN);								//XOR GPIOB output data register to invert the selected pin
}

void Toggle_C(int C_PIN){
	GPIOC->ODR^=(1u<<C_PIN);
}

void Set_B(int B_PIN, int state){
	if (state == 1){
		GPIOB->ODR |= (1u<<B_PIN);
	}
	else{
		GPIOB->ODR &= ~(1u<<B_PIN);
	}
}

void Set_C(int C_PIN, int state){
	if (state == 1){
		GPIOC->ODR |= (1u<<C_PIN);
	}
	else{
		GPIOC->ODR &= ~(1u<<C_PIN);
	}
}





