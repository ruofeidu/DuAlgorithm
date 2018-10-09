%% line fitting 1
x = 0:0.05:1; 
y = 2*x + 1;
a = line_fitting(x, y, true); 
b = line_fitting_total(x, y, true); 
sum((a*x+b-y).^2)


%% line fitting 2
x = 0:0.05:1;
y = 2*x + 1 + 0.1*rand(size(x));
line_fitting(x, y, true); 

%% line fitting 3
x = 0:0.05:1;
y = (abs(x-0.5)<0.25) .* (x+1) + (abs(x-0.5)>=0.25).*(-x);
line_fitting(x, y, true); 

%% line fitting 33
x = 0:0.05:1;
y = 2*x + 1;
x = x + 0.1*rand(size(x)); 
y = y + 0.5*rand(size(x));
line = line_fitting(x, y, true); 

%% line super fitting 1
x = 0.5;
y = 0:0.05:1;
line_fitting(x, y, true); 

%% line super fitting 2
x = 0:0.05:1;
y(:) = 0.5;
line_fitting(x, y, true); 
