%% Image Gradient
% Input: image, debug
% Output: gradient in x & y
% Arthor: Ruofei Du
function [Dx, Dy] = image_gradient(image, debug)
if (nargin < 2) debug = false; end;

if debug
    f = double(imread('swanbw.jpg'));
else
    f = double(image); 
end

% replicate
[h, w] = size(f);
g = [f(:,1), f, f(:,w)];
f = [g(1,:); g; g(h,:)];

% [Dx, Dy] = gradient(f);
Dx = (circshift(f, [0, -1]) - circshift(f, [0, 1])) / 2;
Dy = (circshift(f, [-1, 0]) - circshift(f, [1, 0])) / 2;

Dx = Dx(2:(h+1), 2:(w+1));
Dy = Dy(2:(h+1), 2:(w+1));

% visualization with y upflip
if debug
    [x, y] = meshgrid(1:w, h:-1:1); 
    quiver(x, y, Dx, Dy)
end
