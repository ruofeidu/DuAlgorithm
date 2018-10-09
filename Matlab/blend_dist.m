function [ res ] = blend_dist( x, y, cx, cy )
res = ((x-cx)^2 + (y-cy)^2)^2;
end

