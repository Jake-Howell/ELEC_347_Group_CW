#ifndef _FILTER_H__
#define _FILTER_H__
#include <stm32f4xx.h>
#include <math.h>
#define pi 3.14159265358979323846f

typedef struct {
			float a[3];
			float b[3];
		}coeffs_t;

class Filter{
	public:
		Filter(unsigned int Fs, unsigned int Fo, unsigned int Qfac, unsigned int boost);
		void FilterCalc();
		unsigned short FilterStream(short newSample);
		coeffs_t getCoeffs(void);
		void setCoeffs(coeffs_t coeffs);
		
		
	
	
	private:
		void BZT(float HSnum[], float HSden[]);
		unsigned int Fs, Fo, Qfac, boost;
		float a[3] = {0,0,0}, b[3] = {0,0,0};					//Filter coeff's
		short x[3] = {0,0,0}, y[3] = {0,0,0};					//input and output samples
		unsigned short n = 0;
		
		
		
};


#endif
