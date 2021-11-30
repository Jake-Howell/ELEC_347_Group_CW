%plot frequency response of a discrete filter with sampling frequency 96Khz
%centre frequency 7850 and Quality factor of 2

clc
clear all

Fs = 96000;
F0 = 8150;
Qfac = 2;

FilterPlot(Fs, F0, Qfac);

fig = uifigure;
sld = uislider(fig,...
               'ValueChangingFcn',@(sld,event) sliderMoving(event)); 
sld.Limits = [300 16000];
sld.Value = 8150;


function sliderMoving(event)
  
    F0update = event.Value;
    FilterPlot(96000, F0update, 2);

end
          





