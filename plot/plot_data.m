%% Import data from text file
% Script for importing data from the following text file:
%
%    filename: /home/alefir/repos/obc-gui/plot/hotfire.csv
%
% Auto-generated by MATLAB on 05-Sep-2019 11:24:46

%% Setup the Import Options
opts = delimitedTextImportOptions("NumVariables", 10);

% Specify range and delimiter
opts.DataLines = [2, Inf];
opts.Delimiter = ",";

% Specify column names and types
opts.VariableNames = ["TIME", "BRD", "CH4", "LOX", "HEL", "CBR", "REG", "UAF", "HALLCH4", "HALLLOX", "BAT"];
opts.VariableTypes = ["double", "double", "double", "double", "double", "double", "double", "double", "double", "double", "double"];
opts.ExtraColumnsRule = "ignore";
opts.EmptyLineRule = "read";

% Import the data
hotfire = readtable("/example/path", opts);


%% Clear temporary variables
clear opts

%% Plot Graph
% Convert ISO Epoch Time to Matlab DateTime
x = datetime(hotfire{:,1}, 'convertfrom', 'epochtime','TicksPerSecond',1000);

% Grab only tank pressures
y = hotfire{:,3:5};

% Grab all datapoints
%y = hotfire{:,3:};

h = plot(x,y); hold on;
title('The Data');
xlabel('Time');
datetick('x','H:M:S','keeplimits');
ylabel('Pressure (psi) \ Temperature(C) \ Voltage (V)');
%xlim([datetime(2019,08,17,19,33,0) datetime(2019,08,17,19,36,0)]);
%ylim([-50 3700]);
hold off;


loxHall = hotfire{:,10};
loxChanged = logical(diff(loxHall)~=0);
loxIndexes = find(loxChanged);
for i = 1:numel(loxIndexes)
    xline(x(loxIndexes(i)));
end

% Add legend for only tanks
legend(h(1:3), 'CH4 Tank', 'LOX Tank', 'HEL Tank');

% Add legend for all data
%legend(h(1:11), 'CH4 Tank', 'LOX Tank', 'HEL Tank', 'Chamber Pres', 'HEL Reg', 'UAF TC', 'CH4 Hall', 'LOX Hall', 'BATTERY');
