function [ res ] = affine_transformation( p1, p2 )
% p1, p2: 2*3
% p2 = A * [p1; ones(1,3)]; 
res = p2 / [p1; ones(1,3)];
end

