clc
clear all

Fs = 96000;
F0 = 8150;
Qfac = 2;
boost = -20:4:20;
FilterPlot(Fs, F0, Qfac, boost);

fig = uifigure;
sld = uislider(fig,...
               'ValueChangingFcn',@(sld,event) sliderMoving(event, boost)); 
sld.Limits = [300 16000];
sld.Value = 8150;


function sliderMoving(event, boost)
  
    F0update = event.Value;
    FilterPlot(96000, F0update, 2, boost);

end
          





