%script for testing the filter by passing audio files through it at
%different boost/cut levels and centre frequencies
clc
clear all

Fs = [44100 48000 96000]; %standard sample rates
F0 = 8150; %centre frequency for boosting/cutting
boost = 0; %boost/cut value
Qfac = 2; %quality factor
duration = 5; %clip duration in seconds

%array of audio file names at different sampling frequencies
AudioFiles44k = {'440737__lamont-roberts__sweep001.wav', '419028__realdavidfloat__kick-snare-loops-reverb-variations-120bpm.wav'}; 
AudioFiles48k = {'448213__florianreichelt__white-noise.wav'}; 

%TURN DOWN VOLUME IF USING HEADPHONES - THIS CAN HURT YOUR EARS
FilterTest(Fs(1), F0, Qfac, boost, AudioFiles44k, 2, duration);
%                                                ^^^ this variable
%controls which file from the audio file array you wish to play

