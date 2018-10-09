%% Gradient Magnitude Direction Function
% Input: Gradient [Dx, Dy]
% Output: R, magnitude 
%         X, cos(direction)
%         Y, sin(direction)
% Arthor: Ruofei Du
function [R, X, Y] = gradient_magnitude_direction(Dx, Dy, debug)
if (nargin < 3) debug = false; end;

if debug
    f = double(imread('swanbw.jpg'));
    [Dx, Dy] = image_gradient(f); 
else
    Dx = double(Dx);
    Dy = double(Dy); 
end

R = sqrt(Dx .* Dx + Dy .* Dy); 
X = Dx ./ R;
Y = Dy ./ R;

% visualization with y upflip
if debug
    n = size(f, 1); 
    m = size(f, 2);
    [x, y] = meshgrid(1:m, n:-1:1); 
    quiver(x, y, Dx, Dy); 
end
