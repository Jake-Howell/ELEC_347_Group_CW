function Filtercalc(Fs, Fo, Qfac) %inputs are sampling frequency, centre frequency and quality factor
%function create a digital bell filter based on frequency and quality
%factor inputs
%plots the magnitude response of the filter at different boost/cut levels
%between -20 and 20dB in 4dB steps

boost = -20:4:20; %boost/cut range
L = length(boost); %calculate vector length

G = zeros(1, L); %preallocate gain vector
k = zeros(1, L); %preallocate k vector

for c = 1:L %repeat for length of boost vector (number of steps between -20 and 20)
    G(c) = 10^(boost(c)/20); %calculate gain
    k(c) = 3*((G(c) -1)/(G(c) + 1)); %calculate k
end

%prealloacate for speed
Wo = zeros(1, L);
Wo2 = zeros(1, L);
HSnum = zeros(L,3);
HSden = zeros(L,3);

b = zeros(L,3);
a = zeros(L,3);

for i = 1:L %repeat for number of steps
    
    Wo(i) =  2*pi*Fo; %calculate centre frequency in Radians per second
    Wo2(i) = Wo(i)^2; %centre frequency in Rads/s squared

    HSnum(i,:) = [1 ((3+k(i))*(Wo(i)/Qfac)) (Wo2(i))]; %calculate continuous transfer function numerator
    HSden(i,:) = [1 ((3-k(i))*(Wo(i)/Qfac)) (Wo2(i))]; %calculate continuous transfer function denominator
     
    [b(i,1:3), a(i,1:3)] = bilinear(HSnum(i,1:3), HSden(i,1:3), Fs, Fo); %calc BZT coefficients for each iteration of the continuous TF

end

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

