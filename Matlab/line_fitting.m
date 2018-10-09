%% Single Line Fitting
% Input: x, y
% Output: line(2)
% Author: Ruofei Du
function [ res ] = line_fitting(x, y, draw, debug)
%line fitting
%   fit a line
if (nargin < 2) debug = true; elseif (nargin < 4) debug = false; end
if (nargin <= 2) draw = false; end

if (debug)
    x = 0:0.05:1;
   y = 2*x + 1 + 0.1*rand(size(x));
   %x(:) = 0.5;
   %  y = 0:0.05:1;
end
n = size(x, 2); 
L = [ sum(x.^2), sum(x); sum(x), n]; 
R = [ sum(x.*y), sum(y) ]; 

if (debug || draw)
    plot(x, y, 'bo', 'MarkerSize', 10); hold on;
end

zero = 1e-6;
if abs(det(L)) > zero
    res = R / L; 
    if (debug || draw)
        plot(x, res(1)*x+res(2),'r');
    end
else
    res(1) = NaN;
    res(2) = mean(x);
    if (debug || draw)
        plot([res(2), res(2)], [min(y), max(y)], 'r')
    end
end

end

