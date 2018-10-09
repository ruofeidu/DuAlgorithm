function J = interpolate_gradients(R, Dx, Dy)
% R is an image-sized matrix containing the magnitude of the image
% gradients.  Dx and Dy are corresponding image-sized matrices, containing
% the x and y components of the direction of the gradient.  
% J will be an identically-sized matrix.  J(i,j) contains the magnitude of
% the gradient at position (i+Dx(i,j), j+Dy(i,j)).  Of course, i+Dx(i,j)
% and j+Dy(i,j) are not integer positions; this is why we need to
% interpolate.
[h, w] = size(R);
X = (ones(h,1)*(1:w)) + Dx;
Y = ((1:h)'*ones(1,w)) + Dy;
J = interp2(R, X, Y);

