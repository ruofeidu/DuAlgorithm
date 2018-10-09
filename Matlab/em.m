%% Expectation-Maximization for two lines
% Input: x, y
% Output: line(2)
% Author: Ruofei Du
function [ res ] = em(x, y, classes, draw, debug)
% line fitting
if (nargin < 2) debug = true; elseif (nargin < 4) debug = false; end
if (nargin <= 2) draw = false; end
if (nargin <= 2) classes = 2; end

if (debug)
    x = 0:0.02:1;
    y = (abs(x-0.4)<0.25) .* (x+4) + (abs(x-0.5)>=0.25).*(-x);
    y = y + 0.7*randn(size(x));
end

n = size(x, 2); 
w1 = zeros(n);  w2 = zeros(n); 
r1 = zeros(n);  r2 = zeros(n); 
a1 = rand();    b1 = rand(); 
a2 = rand();    b2 = rand(); 
res1 = zeros(2); res2 = zeros(2); 
sigma = 0.04;
converge = false; 
count = 0; 
error = 0; 
min_error = 1e-4; 
max_count = 1000; 
threshold = 0.1;
err_threshold = 5;
previous_error = -1;

while ~converge
    % expectation
    count = count + 1; 
    r1 = a1 * x + b1 - y; 
    r2 = a2 * x + b2 - y; 
    w1 = gauss(r1, sigma) ./ (gauss(r1, sigma) + gauss(r2, sigma)); 
    w2 = gauss(r2, sigma) ./ (gauss(r1, sigma) + gauss(r2, sigma)); 
    for i = 1 : n
        if r1(i)^2 - r2(i)^2 > threshold
            w1(i) = 0; 
            w2(i) = 1; 
        elseif r2(i)^2 - r1(i)^2 > threshold
            w1(i) = 1; 
            w2(i) = 0; 
        end
    end
    
    % maximization
    res1 = line_fitting_w(x, y, w1); 
    res2 = line_fitting_w(x, y, w2); 
    
    y1 = res1(1)*(w1.*x) + res1(2); 
    y2 = res2(1)*(w2.*x) + res2(2);
    
    err1 = sum(w1.*abs(y-y1).^2) + sum(w2.*abs(y-y2).^2); 
    err2 = sum(w2.*abs(y-y1).^2) + sum(w1.*abs(y-y2).^2); 
    error = min(err1, err2); 
    if (error < err_threshold && error == previous_error) converge = true; end;
    previous_error = error; 
    fprintf('Iteration %d: error %d %f %f\n', count, error, res1(1), a1); 
    % next
    a1 = res1(1); b1 = res1(2); 
    a2 = res2(1); b2 = res2(2); 
    if (count > max_count) converge = true; end; 
    
    
end
figure;
hold on;
subplot(3,1,1);  
plot(x, y, 'bo', 'MarkerSize', 10); hold on; 
plot(x, res1(1)*x+res1(2), 'k-'); 
plot(x, res2(1)*x+res2(2), 'r-'); 
subplot(3,2,3); bar(r1,'r');  subplot(3,2,4); bar(w1,'b'); 
subplot(3,2,5); bar(r2,'r');  subplot(3,2,6); bar(w2,'b'); 
end
