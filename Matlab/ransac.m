function [ res ] = ransac( M )
%ransac
% p1 = 100*rand(2,8);
% A = 100*rand(2,3);
% p2 = A*[p1; ones(1,8)];
% p1 = [p1, 100*rand(2,16)];
% p2 = [p2, 100*rand(2,16)];
% M = [p1', p2', ones(24,1)];

n = size(M, 1); 
ransac_steps = 100000; 
err = 0; 
T = zeros(2, 3); 
idx = randperm(n); 
best = 0; 
res = 0; 

for step = 1 : ransac_steps
idx = randperm(n); 
p1 = M(idx(1:3), 1:2); 
p2 = M(idx(1:3), 3:4); 
x = [p1'; ones(1,3)];
if (rank(x) < 3) continue; end;
T = affine_transformation(p1', p2'); 
p3 = T * [M(:, 1:2)'; ones(1, n)];
err = sqrt((p3(1, :) - M(:, 3)').^2 + (p3(2, :) - M(:, 4)').^2);
num = sum(err < 2); 
if num > best
    best = num; 
    res = T; 
end
    
end

end

