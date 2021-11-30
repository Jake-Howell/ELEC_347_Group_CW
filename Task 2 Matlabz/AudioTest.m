clc
clear all

Fs = 48000; 
F0 = 2000;
boost = 20;
Qfac = 2;

%TURN DOWN VOLUME IF USING HEADPHONES
FilterTest(Fs, F0, Qfac, boost);


