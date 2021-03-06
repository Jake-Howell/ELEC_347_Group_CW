/*
Program written by Jacob Howell
December, 2021
Module: ELEC 347
Task 4: Real Time Implementation of parametric EQ
*/
#include "filter.h"

Filter::Filter(float coeff_A[3], float coeff_B[3]){
	for (int i = 0; i < 3; i++){
		this->a[i] = coeff_A[i];
		this->b[i] = coeff_B[i];
	}
}

void Filter::FilterCalc(){				//Function not used
	short G,K;
	float Wo, Wo2;						//Center Freq in rads per second, wo2 is Wo squared
	//float HSnum[3], HSden[];	//Continuous time transfer functions
//	float a[3], b[3]; 				//Descreet time transfer functions
	G = pow(10, (boost/20));	//convert to linear gain
	K = 3*((G-1)/(G+1));			//calculate K
	
	Wo  = 2*pi*Fo;	//calculate center frequency in radiens per second
	Wo2 = Wo*Wo;		//calculate Wo squared 
	
	float HSnum[3] = {1, ((3+K)*(Wo/Q)), Wo2}; //Continuous time transfer function numerator
	float HSden[3] = {1, ((3-K)*(Wo/Q)), Wo2}; //Continuous time transfer function denominator
	
	//Filter::BZT(HSnum,HSden);
	
}

void Filter::BZT(float HSnum[], float HSden[]){		//Function not used
	a[0] = (HSden[0] + HSden[1] + HSden[2]); 
	a[1] = (2*(-HSden[0] + HSden[2]))/a[0]; 
	a[2] = (HSden[0] - HSden[1] + HSden[2])/a[0]; 
	
	b[0] = HSnum[0] + HSnum[1] + HSnum[2]/a[0]; 
	b[1] = (2*(-HSnum[0] + HSnum[2]))/a[0]; 
	b[2] = (HSnum[0] - HSnum[1] + HSnum[2])/a[0];
	
	a[0] =1;
}

short Filter::FilterStream(short newSample){	//take current sample, return output
	float Y = 0.0f;															//
	
	
	//shift buffer values
	x[2]=x[1];
	x[1]=x[0];
	x[0] = (float)newSample;
	
	y[2]=y[1];
	y[1]=y[0];
	
	
	//perform MAC opperations with coeffs and samples
	Y = ( 
			-(a[1]*y[1]) 
			-(a[2]*y[2])
			+(b[0]*x[0]) 
			+(b[1]*x[1]) 
			+(b[2]*x[2])
			);	//current filtered output

	y[0] = Y;					//copy to y buffer
		
	return (short)Y;	//return sample in as short
}
	
coeffs_t Filter::getCoeffs(void){		//return current coeffs 
	coeffs_t coeffs;
	coeffs.a[0] = a[0]; 
	coeffs.a[1] = a[1]; 
	coeffs.a[2] = a[2]; 
	coeffs.b[0] = b[0]; 
	coeffs.b[1] = b[1]; 
	coeffs.b[2] = b[2]; 
	return coeffs;
}

void Filter::setCoeffs(coeffs_t coeffs){	//update coeffs
	
	this->a[0] = coeffs.a[0]; 
	this->a[1] = coeffs.a[1]; 
	this->a[2] = coeffs.a[2]; 
	this->b[0] = coeffs.b[0]; 
	this->b[1] = coeffs.b[1]; 
	this->b[2] = coeffs.b[2]; 
}
