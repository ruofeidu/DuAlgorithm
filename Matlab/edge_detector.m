function o = edge_detector(image, sigma, threshold, debug)
if (nargin < 4) debug = false; end;

if debug
    f = double(imread('swanbw.jpg'));
    sigma = 2; 
    threshold = 15; 
else
    f = double(image); 
end
    
f = smooth_image(f, sigma); 
[Dx, Dy] = image_gradient(f);
[R, X, Y] = gradient_magnitude_direction(Dx, Dy); 
J = interpolate_gradients(R, X, Y);
J_inv = interpolate_gradients(R, -X, -Y);
o = R > threshold & R > J & R > J_inv;

imwrite(o, 'swan_edge.jpg'); 

end
