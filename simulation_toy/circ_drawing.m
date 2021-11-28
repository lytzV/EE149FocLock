crc = @(r,p,a) [r*cosd(a + p);  r*sind(a + p)];
t = linspace(0, 360, 361);                              % Time
init_pos = 25;                                          % Initial Position (°)
radius = 1.2;
locus = crc(radius, init_pos, t);
figure(1)
for k1 = 2:length(t)
    plot(locus(1,k1),  locus(2,k1), 'gp')
    axis([-1.5  1.5    -1.5  1.5])
    grid
    axis square
    drawnow    
end