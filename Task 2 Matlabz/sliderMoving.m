function sliderMoving(event, boost)
  
    F0update = event.Value;
    disp(F0update);
    FilterPlot(96000, F0update, 2, boost);

end

