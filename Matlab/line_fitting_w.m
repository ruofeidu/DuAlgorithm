%% Single Line Fitting
% Input: x, y
% Output: line(2)
% Author: Ruofei Du
function [ res ] = line_fitting_w(x, y, w, draw, debug)
%line fitting
%   fit a line
if (nargin < 3) debug = true; elseif (nargin < 4) debug = false; end
if (nargin <= 3) draw = false; end

if (debug)
     %  x(:) = 0.5;
    %y = 0:0.05:1;
    
    x = 0:0.05:1;
    y = (abs(x-0.5)<0.25) .* (x+1) + (abs(x-0.5)>=0.25).*(-x);

 
    n = size(x, 2); 
    w = ones(1, n); 
    w(7:15) = 0; 
    w = ~w; 
    %r = rand() * x + rand() - y;
    %w = exp((-r.^2)/(sigma.^2)) ./ sum(exp((-r.^2)/(sigma.^2)));
end
n = size(x, 2); 
L = [ sum(w.*(x.^2)), sum(w.*x); sum(w.*x), sum(w)]; 
R = [ sum(w.*x.*y), sum(w.*y) ]; 

if (debug || draw)
    plot(x, y, 'bo', 'MarkerSize', 10); hold on;
end

if det(L) ~= 0
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

