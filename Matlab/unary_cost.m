function [ dist ] = unary_cost( L, R, MAXD )
%unary matching costs
[m, n] = size(L); 
dist = zeros(m, n, MAXD); 
L = double(L);  R = double(R); 

for i = 1 : m
    for d = 0 : MAXD-1
        for j = 1 : d
            dist(i,j,d) = 255*255; 
        end
        for j = d+1 : n
            dist(i,j,d+1) = (L(i,j) - R(i,j-d))^2;
        end
    end
end
end

