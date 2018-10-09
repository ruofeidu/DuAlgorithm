function [ res ] = energy(D, P, dist)
% the energy function by the Potts model
[m, n] = size(D); 
dir = [-1,0;1,0;0,1;0,-1]; 

res = 0; 
for d = 1 : 4
    for k = 1 : m*n
        i = floor((k-1)/n)+1; 
        j = floor(mod(k-1,n))+1;
        a = i + dir(d, 1); 
        b = j + dir(d, 2); 
        if (a<1 || a>m || b<1 || b>n) continue; end;
        res = res + P(i,j,d) * (D(i,j) ~= D(a,b));
    end
end

for k = 1 : m*n
    i = floor((k-1)/n)+1; 
    j = floor(mod(k-1,n))+1;
    res = res + dist(i, j, D(i,j)); 
end

end
