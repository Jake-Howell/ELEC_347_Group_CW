function  [b, a] = ManualFilterCalc(Fs, Fo, Qfac, boost) 
%inputs are sampling frequency, centre frequency, 
%quality factor and boost level
%calculate the coefficients for a range of bell filters with different
%boost and cut levels

G = 10^(boost/20); %calculate gain
k = 3*((G -1)/(G + 1)); %calculate k

Wo =  2*pi*Fo; %calculate centre frequency in Radians per second
Wo2 = Wo^2; %centre frequency in Rads/s squared

HSnum = [1 ((3+k)*(Wo/Qfac)) (Wo2)]; 
%calculate continuous transfer function numerator
HSden = [1 ((3-k)*(Wo/Qfac)) (Wo2)]; 
%calculate continuous transfer function denominator
   
a = zeros(3:1);
a(1) = (HSden(1) + HSden(2) + HSden(3));
a(2) = (2*(-HSden(1) + HSden(3))/a(1));
a(3) = ((HSden(1) - HSden(2) + HSden(3))/a(1));

b = zeros(3:1);
b(1) = (HSnum(1) + HSnum(2) + HSnum(3)/a(1));
b(2) = (2*(-HSnum(1) + HSnum(3))/a(1));
b(3) = ((HSnum(1) - HSnum(2) + HSnum(3))/a(1));

a(1) = a(1)/a(1);

az = poly(a);
bz = poly(b);
freqz(bz,az, 2^15, Fs);

disp('b');
disp(b);
disp('a');
disp(a);


end

