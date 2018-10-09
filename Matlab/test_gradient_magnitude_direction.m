function [R, X, Y] = test_gradient_magnitude_direction()
Dx = ones(4,1)*(1:4);
Dy = (1:4)'*ones(1,4);
[R, X, Y] = gradient_magnitude_direction(Dx,Dy);