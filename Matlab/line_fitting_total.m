%% Single Line Fitting Total Least Squares Method
% Input: x, y
% Output: line(2)
% Author: Ruofei Du
function [ res ] = line_fitting_total(x, y, draw, debug)
%line fitting
%   fit a line
if (nargin < 2) debug = true; elseif (nargin < 4) debug = false; end
if (nargin <= 2) draw = false; end

if (debug)
    x = 0:0.05:1;
    y = 2*x + 1 + 0.1*rand(size(x));
    x(:) = 0.5;
    y = 0:0.05:1;
end
n = size(x, 2); 
sy = sum(y) ./ n; 
sx = sum(x) ./ n; 
sxy = sum(x .* y); 
sy2 = sum(y .^ 2); 
sx2 = sum(x .^ 2); 
B = 0.5 .* (((sy2 - n.*sy.^2)-(sx2-n.*sx.^2))./(n.*sx.*sy-sxy));
R = corrcoef(x, y); % [ sum(x.*y), sum(y) ]; 
b1 = -B + (B.^2+1).^0.5;
b2 = -B - (B.^2+1).^0.5;
a1 = sy - b1.*sx;
a2 = sy - b2.*sx;

if (debug || draw)
    plot(x, y, 'bo', 'MarkerSize', 10); hold on;
end


if R(1,2) > 0; 
    res = [b1, a1];
else
    res = [b2, a2]; 
end

if isinf(res(2))
    res(2) = mean(x);
    if (debug || draw)
        plot([res(2), res(2)], [min(y), max(y)], 'r');
    end
else
    if (debug || draw)
        plot(x, res(1)*x+res(2),'r');
    end
end

end

