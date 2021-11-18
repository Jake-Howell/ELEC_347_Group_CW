Qfac = 2; %q factor
Fs = 96000; %sampling frequency
Fo = 7850; %centre frequency
boost = 20; 
k = 3*((boost -1)/(boost + 1));

FreqRange = [300 16000]; %band edge frequencies
Wc = 2*pi*FreqRange(2); %convert upper cutoff to radians
Wp = [tan((2*pi*FreqRange(1))/(2*Fs)) tan((2*pi*FreqRange(2))/(2*Fs))]; %prewarp cutoff frequencies
Wo2 = Wp(1)*Wp(2); %calculate Wo2
Wo =  2*pi*Fo;

Bw = (2*pi*(FreqRange(2) -FreqRange(1)))/Fs; %calculate bandwidth and convert to rads per sample


HSnum = [1 ((3+k)*(Wo/Qfac)) (Wo2)]; %continuous transfer function numerator
HSden = [1 ((3-k)*(Wo/Qfac)) (Wo2)]; %continuous transfer function denominator

disp(HSnum);
disp(HSden);

figure(1);
[Ha, Wa] = freqs(HSnum, HSden); %plot continuous freq response
Fa = Wa/(2*pi);
plot(Fa, 20*log10(abs(Ha)))
hold on

figure(2);
plot(Fa, angle(Ha)*180/pi); %plot continuous phase response
hold on

figure(1);
[b1, a1] = bilinear(HSnum, HSden, Fs, Fo); %calc BZT coeffs
[Hd, Fd] = freqz(b1, a1, 2^15, Fs);
plot(Fd, 20*log10(abs(Hd)), 'r:') %Plot discrete BZT magnitude response

figure(2);
plot(Fd, angle(Hd)*180/pi, 'r:') %plot discrete BZT phase response

figure(1);
[b2, a2] = impinvar(HSnum, HSden, Fs); %calc imp. invar filter coeff
[Hd, Fd] = freqz(b2, a2, 2^15, Fs);
plot(Fd, 20*log10(abs(Hd)), 'g:') %plot imp. invar mag response
axis([0 Fs 0 30])
ylabel('Magnitude (dB)')
xlabel('Frequency (Hz)')
title('Analogue & Digital Filter Responses')
legend('Analogue', 'BZT', 'Impulse Invariant');

figure(2);
plot(Fd, angle(Hd)*180/pi, 'g:') %impInvar phase resp
axis([0 50000 -100 100])
ylabel('Phase (Degrees)')
xlabel('Frequency (Hz)')
title('Analog & Digital Filter Responses')
legend('Analog', 'BZT', 'Impulse Invariant');





