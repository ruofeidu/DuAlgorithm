%% Smooth Function
% Input: image, sigma, debug
% Output: smoothed image
% Arthor: Ruofei Du
function o = smooth_image(image, sigma, debug)
if (nargin < 3) debug = false; end;

if debug
    f = double(imread('swanbw.jpg'));
else
    f = double(image); 
end

%g = fspecial('gaussian', [sigma*6+1 sigma*6+1], sigma); 
n = sigma * 3;
[x, y] = meshgrid(-n : n, -n : n);
g = exp(- (x .^ 2 + y .^ 2) / (2 * sigma ^ 2));
g = g / sum(g(:));

o = imfilter(f, g, 'replicate');

if debug
    subplot(1, 2, 1);
    imshow(f); 
    subplot(1, 2, 2);
    imshow(o);
end