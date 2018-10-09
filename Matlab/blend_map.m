function [ w ] = blend_map( height, width )
w = zeros(height, width); 
cy = height / 2; 
cx = width / 2; 
for i = 1 : height
    for j = 1 : width
        %w(i,j) = 1 / sqrt((i-cy)^2+(j-cx)^2);
        w(i,j) = blend_dist(j,i,cx,cy); 
    end
end

end

