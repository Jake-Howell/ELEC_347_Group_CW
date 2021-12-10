#include "filter.h"

Filter::Filter(unsigned int Fs, unsigned int Fo, unsigned int Q, int boost){
	this->Fs 		= Fs;
	this->Fo 		= Fo;
	this->Q 	=	Q;
	this->boost = boost;
	FilterCalc();					//calculate filter coeff's 'a' and 'b'
}

void Filter::FilterCalc(){
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

void Filter::BZT(float HSnum[], float HSden[]){
	a[0] = (HSden[0] + HSden[1] + HSden[2]); 
	a[1] = (2*(-HSden[0] + HSden[2]))/a[0]; 
	a[2] = (HSden[0] - HSden[1] + HSden[2])/a[0]; 
	
	b[0] = HSnum[0] + HSnum[1] + HSnum[2]/a[0]; 
	b[1] = (2*(-HSnum[0] + HSnum[2]))/a[0]; 
	b[2] = (HSnum[0] - HSnum[1] + HSnum[2])/a[0];
	
	a[0] =1;
}

short Filter::FilterStream(short newSample){
	float Y = 0.0f;
	
	x[2]=x[1];
	x[1]=x[0];
	x[0] = (float)newSample;
	
	y[2]=y[1];
	y[1]=y[0];
	
	Y = ( 
			-(a[1]*y[1]) 
			-(a[2]*y[2])
			+(b[0]	*x[0]	 ) 
			+(b[1]*x[1]) 
			+(b[2]*x[2])
			);	//current filtered output

	y[0] = Y;
	
	//n = (n + 1)%3;
	
	
	
	return (short)Y;
}
	
coeffs_t Filter::getCoeffs(void){
	coeffs_t coeffs;
	coeffs.a[0] = a[0]; 
	coeffs.a[1] = a[1]; 
	coeffs.a[2] = a[2]; 
	coeffs.b[0] = b[0]; 
	coeffs.b[1] = b[1]; 
	coeffs.b[2] = b[2]; 
	return coeffs;
}

void Filter::setCoeffs(coeffs_t coeffs){
	
	this->a[0] = coeffs.a[0]; 
	this->a[1] = coeffs.a[1]; 
	this->a[2] = coeffs.a[2]; 
	this->b[0] = coeffs.b[0]; 
	this->b[1] = coeffs.b[1]; 
	this->b[2] = coeffs.b[2]; 
}
