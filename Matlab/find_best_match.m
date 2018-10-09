function [ res ] = find_best_match( F1, D1, F2, D2 )
% J = imread('LR1bw.jpg');
% [F2, D2] = vl_sift(single(J));
% K = imread('LR2bw.jpg');
% [F3, D3] = vl_sift(single(K));
% F1 = F2; F2 = F3; D1 = D2; D2 = D3; 

F1 = F1'; F2 = F2'; D1 = D1'; D2 = D2';
      
n = size(F1, 1); 
m = size(F2, 1); 
res = zeros(m, 5); 
res(:, 3:4) = F2(:, 1:2);

for i = 1 : m
    SSD = (repmat(D2(i,:), n, 1) - D1).^2;
    SSD = sum(SSD, 2);
    [minSSD, index] = sort(SSD);
    res(i, 1:2) = F1(index(1), 1:2); 
    res(i, 5) = minSSD(1); 
end

% [M, index] = sortrows(res, 5); 
% figure; 
% subplot(1, 2, 1); imshow(J); hold on; 
% plot(M(1,1),M(1,2),'.','Markersize',20,'color',[1 0 0]);
% plot(M(2,1),M(2,2),'.','Markersize',20,'color',[0 1 0]);
% plot(M(3,1),M(3,2),'.','Markersize',20,'color',[0 1 1]);
% 
% subplot(1, 2, 2); imshow(K); hold on; 
% plot(M(1,3),M(1,4),'.','Markersize',20,'color',[1 0 0]);
% plot(M(2,3),M(2,4),'.','Markersize',20,'color',[0 1 0]);
% plot(M(3,3),M(3,4),'.','Markersize',20,'color',[0 1 1]);

end

