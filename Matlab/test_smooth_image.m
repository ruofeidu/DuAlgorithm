function o = test_smooth_image()
I = zeros(9,9);
I(4:6, 4:6) = 255;
o = smooth_image(I, 1);