function [] = FilterPlot(Fs, Fo, LowerCutoff, UpperCutoff, Qfac)
%SLIDER Summary of this function goes here
%   Detailed explanation goes here

boost = 1;

[HSnum, HSden, Fa, Fb] = Filtercalc(Fs, Fo, LowerCutoff, UpperCutoff, Qfac, boost);

sys = tf(HSnum, HSden);
f = figure;
ax = axes('Parent',f,'position',[0.13 0.39  0.77 0.54]);
h = bodeplot(sys);
%setoptions(h,'XLim',[0,20000],'YLim',[0,30]);

b = uicontrol('Parent',f,'Style','slider','Position',[81,54,419,23],...
              'value',boost, 'min',1, 'max',50);
bgcolor = f.Color;
bl1 = uicontrol('Parent',f,'Style','text','Position',[50,54,23,23],...
                'String','1','BackgroundColor',bgcolor);
bl2 = uicontrol('Parent',f,'Style','text','Position',[500,54,23,23],...
                'String','50','BackgroundColor',bgcolor);
bl3 = uicontrol('Parent',f,'Style','text','Position',[240,25,100,23],...
                'String','Gain','BackgroundColor',bgcolor);

b.Callback = @(es,ed) updateSystem(h, );



end

