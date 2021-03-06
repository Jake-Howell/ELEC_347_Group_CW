function FilterTest(Fs, F0, Qfac, boost, AudioFiles, i, duration)
%takes a .wav file and passes it through a bell filter

[L, b, a] = FilterCalc(96000, F0, Qfac, boost); 
%calculate filter coefficients, discard L

DataIn = audioread(AudioFiles{1,i}); 
%27 - 4khz frequency sweep

filteredsignal = filter(b,a,DataIn); 
%pass audio file through the filter

player = audioplayer(filteredsignal, Fs); 
%create an audio player object with the filtered signal

%play the audio clip
play(player);
pause(duration);
stop(player);
end

