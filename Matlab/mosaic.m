function [ res ] = mosaic( J, K )
% mosaic two images
%   sift, find best matches, stitch
[F2, D2] = vl_sift(single(J));
[F3, D3] = vl_sift(single(K));
M = find_best_match(F3, D3, F2, D2);
A = ransac(M);
A
res = stitch_blend(J, K, A); 
end

