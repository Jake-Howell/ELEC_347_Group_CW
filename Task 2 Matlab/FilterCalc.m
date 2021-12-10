function  [L, b, a] = FilterCalc(Fs, Fo, Qfac, boost) %inputs are sampling frequency, centre frequency, quality factor and boost level
%calculate the coefficients for a range of bell filters with different
%boost and cut levels

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

for i = 1:L %repeat for number of gain steps
    
    Wo(i) =  2*pi*Fo; %calculate centre frequency in Radians per second
    Wo2(i) = Wo(i)^2; %centre frequency in Rads/s squared

    HSnum(i,:) = [1 ((3+k(i))*(Wo(i)/Qfac)) (Wo2(i))]; %calculate continuous transfer function numerator
    HSden(i,:) = [1 ((3-k(i))*(Wo(i)/Qfac)) (Wo2(i))]; %calculate continuous transfer function denominator
     
    [b(i,1:3), a(i,1:3)] = bilinear(HSnum(i,1:3), HSden(i,1:3), Fs, Fo); %calc BZT coefficients for each iteration of the continuous TF
    disp(" ");
    disp("B");
    disp(b);
    disp("A:");
    disp(a);
end

end

