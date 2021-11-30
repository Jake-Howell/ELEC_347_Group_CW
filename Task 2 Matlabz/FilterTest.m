function FilterTest(Fs, F0, boost)
%takes a .wav file and passes it through a bell filter

[L, b, a] = FilterCalc(Fs, F0, boost);

DataIn = audioread(' ');

    

end

