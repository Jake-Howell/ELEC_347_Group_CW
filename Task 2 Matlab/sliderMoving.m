function sliderMoving(event, Fs, Qfac, boost)
  
    %replot filter response when slider is moved
    F0update = event.Value; %get new centre frequency from slider
    disp(F0update); %display value
    FilterPlot(Fs, F0update, Qfac, boost); %replot response

end

