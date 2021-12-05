%Robot Parameters
% Copyright 2017 The MathWorks, Inc.

wheelR = 0.035; %Wheel radius
axleLength = 0.23; %Distance between wheels
ticksPerRot = 2578.33; % Ticks per rotation for encoders
load wheelMotorLUT %Look up table for VEX motors
Ts = 0.01; %Sample time
load wheelMotorModel %Motor model for VEX motors