function [HSnum, HSden, Fa, Fb] = Filtercalc(Fs, Fo, LowerCutoff, UpperCutoff, Qfac, boost)
%FILTERCALC Summary of this function goes here
%   Detailed explanation goes here

k = 3*((boost -1)/(boost + 1));

FreqRange = [LowerCutoff UpperCutoff]; %band edge frequencies
Wc = 2*pi*FreqRange(2); %convert upper cutoff to radians
Wp = [tan((2*pi*FreqRange(1))/(2*Fs)) tan((2*pi*FreqRange(2))/(2*Fs))]; %prewarp cutoff frequencies
Wo2 = Wp(1)*Wp(2); %calculate Wo2
Wo =  2*pi*Fo;

Bw = (2*pi*(FreqRange(2) -FreqRange(1)))/Fs; %calculate bandwidth and convert to rads per sample

HSnum = [1 ((3+k)*(Wo/Qfac)) (Wo2)]; %continuous transfer function numerator
HSden = [1 ((3-k)*(Wo/Qfac)) (Wo2)]; %continuous transfer function denominator

[Ha, Wa] = freqs(HSnum, HSden); %continuous freq response
Fa = Wa/(2*pi);
Fb = 20*log10(abs(Ha));


end

