function FilterTest(Fs, F0, Qfac, boost)
%takes a .wav file and passes it through a bell filter

[L, b, a] = FilterCalc(Fs, F0, Qfac, boost); %calculate filter coefficients, discard L

DataIn = audioread('440737__lamont-roberts__sweep001.wav');

filteredsignal = filter(b,a,DataIn); %pass audio file through the filter

player = audioplayer(filteredsignal, Fs);

%play the first 30 seconds of the audio clip
play(player);
pause(30);
stop(player);
end

