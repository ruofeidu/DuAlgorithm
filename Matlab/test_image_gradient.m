function [Dx Dy] = test_image_gradient()
I = (ones(9,1)*(-4:4)).^2 + ((-4:4)'*ones(1,9)).^2;
[Dx Dy] = image_gradient(I);