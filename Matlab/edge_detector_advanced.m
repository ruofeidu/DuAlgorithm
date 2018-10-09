function o = edge_detector_advanced(image, sigma, threshold, threshold2, debug)
if (nargin < 5) debug = false; end;

if debug
    f = double(imread('swanbw.jpg'));
    sigma = 2; 
    threshold = 15; 
    threshold2 = 2; 
else
    f = double(image); 
end
    
f = smooth_image(f, sigma); 
imshow(f); 
[Dx, Dy] = image_gradient(f);
[R, X, Y] = gradient_magnitude_direction(Dx, Dy); 
J = interpolate_gradients(R, X, Y);
J_inv = interpolate_gradients(R, -X, -Y);

oh = R > threshold & R > J & R > J_inv;
ol = R > threshold2 & R > J & R > J_inv;

flag = true; 

[h, w] = size(f);
dir = [0,1; 0,-1; -1,0; 1,0; -1,-1; -1,1; 1,-1; 1,1];
o = oh; 

% this can be accelerated by a 8*h*w matrix :-)
while flag
   flag = false; 
   for i = 1 : h
       for j = 1 : w
           if ol(i,j) == 1 && o(i,j) == 0
               for k = 1 : 8
                   ni = i + dir(k,1);
                   nj = j + dir(k,2);
                   if (ni >= 1 && ni <= h && nj >= 1 && nj <= w && o(ni, nj) == 1)
                       o(i, j) = 1; 
                       flag = true; 
                   end
               end
           end
       end
   end
end

imwrite(o, 'swan_edge_advanced.jpg'); 

