%% line fitting 1
x = 0:0.05:1; 
y = 2*x + 1;
line_fitting_total(x, y, true); 

%% line fitting 2
x = 0:0.05:1;
y = 2*x + 1 + 0.5*rand(size(x));

subplot(1,2,1); 
p = line_fitting(x, y, true); 
err = 0; 
for i = 1 : length(x)
    err = dis_point_line([x(i),y(i)], [p(1), -1, p(2)]);
end
err
subplot(1,2,2); 
p = line_fitting_total(x, y, true); 
err = 0; 
for i = 1 : length(x)
    err = dis_point_line([x(i),y(i)], [p(1), -1, p(2)]);
end
err

%% line fitting 3
x = 0:0.05:1;
y = (abs(x-0.5)<0.25) .* (x+1) + (abs(x-0.5)>=0.25).*(-x);

subplot(1,2,1); 
p = line_fitting(x, y, true); 
err = 0; 
for i = 1 : length(x)
    err = dis_point_line([x(i),y(i)], [p(1), -1, p(2)]);
end
err
title('Naive Line Fitting (error = )'); 
subplot(1,2,2); 
p = line_fitting_total(x, y, true); 
err = 0; 
for i = 1 : length(x)
    err = dis_point_line([x(i),y(i)], [p(1), -1, p(2)]);
end
title('Naive Line Fitting (error = )'); 
err
%% line fitting 33
x = 0:0.05:1;
y = 2*x + 1;
x = x + 0.1*rand(size(x)); 
y = y + 0.1*rand(size(x));
line = line_fitting_total(x, y, true); 

%% line super fitting 1
x = 0.5;
y = 0:0.05:1;
line_fitting_total(x, y, true); 

%% line super fitting 2
x = 0:0.05:1;
y(:) = 0.5;
line_fitting_total(x, y, true); 
