function FilterPlot(Fs, F0, Qfac, boost)
%calculates and plots the frequency response of a bell filter given
%sampling frequency, centre frequency and boost/cut
[L, b, a] = FilterCalc(Fs, F0, Qfac, boost); 

figure(1); %create plot figure for the frequency response

clf
ylabel('Magnitude (dB)')
xlabel('Frequency (Hz)')
axis([0 Fs -20 20]); %x-axis from 0 to 96Khz, y-axis from -20 to dB
grid on;
hold on

%preallocate matrices for discrete frequency response
Hd = zeros(32768, L); 
Fd = zeros(32768, L);

for x = 1:L %repeat for number of steps
    [Hd(:,x), Fd(:,x)] = freqz(b(x,:), a(x,:), 2^15, Fs); %get frequency response of discrete BZT transfer function
    %Hd: magnitude component
    %Fd: frequency component
    plot(Fd(:,x), 20*log10(abs(Hd(:,x))), 'b') %Plot discrete BZT magnitude response
end


end

