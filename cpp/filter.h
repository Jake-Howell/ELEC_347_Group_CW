/*
Program written by Jacob Howell
December, 2021
Module: ELEC 347
Task 4: Real Time Implementation of parametric EQ
*/
#ifndef _FILTER_H__
#define _FILTER_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <stm32f4xx.h>
#include <math.h>
#define pi 3.14159265358979323846f

typedef struct {
			float a[3];
			float b[3];
		}coeffs_t;

class Filter{
	public:
		Filter(unsigned int Fs, unsigned int Fo, unsigned int Q, int boost);
		void FilterCalc();
		short FilterStream(short newSample);
		coeffs_t getCoeffs(void);
		void setCoeffs(coeffs_t coeffs);
		
		
	
	
	private:
		void BZT(float HSnum[], float HSden[]);
		unsigned int Fs, Fo, Q, boost;
		float a[3] = {1.0f, -1.8657f, 0.8747f}, b[3] = {0.9436f, -1.8657f, 0.9311f};					//Filter coeff's
		float x[3] = {0,0,0}, y[3] = {0,0,0};					//input and output samples
		unsigned short n = 0;
		
		
		
};

#ifdef __cplusplus
}
#endif
#endif
