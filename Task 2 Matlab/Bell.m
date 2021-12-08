%script for testing the frequency response of the bell filter at a set range of
%boost and cut levels, with a variable centre frequency input
clc
clear all

%filter specifications
Fs = 96000; %sampling frequency
F0 = 8150; %centre frequency
Qfac = 2; %quality factor
boost = -20:4:20; %boost/cut

%plot filter
FilterPlot(Fs, F0, Qfac, boost);

%slider component to control centre frequency
fig = uifigure;
sld = uislider(fig,...
               'ValueChangingFcn',@(sld,event) sliderMoving(event, Fs, Qfac, boost)); 
sld.Limits = [300 16000];
sld.Value = 8150;



          





