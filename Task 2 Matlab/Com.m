%testing sending data to a microcontroller

clc
clear all


% now connect the device again, the following will now be successful:
s = serialport('COM1', 9600);

write(s, 'a', 'char');


