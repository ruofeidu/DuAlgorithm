function o = display_sift_features(F, m)
% F is a set of SIFT features.  You will want to have already
% displayed an image in a figure, using imshow.
% Note that m can be used to change the color or type of marker
% used.
if nargin < 2
    m = 'ro';
end
hold on
for i = 1:size(F,2)
    plot(F(1,i), F(2,i), m, 'MarkerSize', F(3,i));
end
hold off
o = 1;
end