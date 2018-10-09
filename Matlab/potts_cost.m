function [ P ] = potts_cost( L, K )
% Pairwise cost for neighboring pixels
[m, n] = size(L); 
P = zeros(m, n, 4); 
L = double(L); 
dir = [-1,0;1,0;0,1;0,-1]; 

for k = 1 : m*n
    i = floor((k-1)/n)+1; 
    j = floor(mod(k-1,n))+1;
    for d = 1 : 4
        a = i + dir(d,1); b = j + dir(d,2);
        if (a<1 || a>m || b<1 || b>n) 
            P(i,j,d) = 0; 
            continue; 
        end;
        if abs(L(a, b)-L(i,j)) <= 5
            P(i,j,d) = K*2; 
        else
            P(i,j,d) = K;
        end
    end
end

end

