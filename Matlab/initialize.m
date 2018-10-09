function [ D ] = initialize( dist )
% initial disparity
[m, n, MAXD] = size(dist); 
D = zeros(m, n); 

for k = 1 : m*n
    i = floor((k-1)/n)+1; 
    j = floor(mod(k-1,n))+1;
    D(i,j) = min(dist(i,j,:));
    for k = 1 : MAXD
        if dist(i,j,k) == D(i,j)
            D(i,j) = k;
            break;
        end
    end
end

end

