function [ res ] = show_3_best( M, J, K )

M = sortrows(M, 5); 
disp(M); 

figure; 
subplot(1, 2, 1); imshow(J); hold on; 
plot(M(1,1),M(1,2),'.','Markersize',20,'color',[1 0 0]);
plot(M(2,1),M(2,2),'.','Markersize',20,'color',[0 1 0]);
plot(M(3,1),M(3,2),'.','Markersize',20,'color',[0 1 1]);

subplot(1, 2, 2); imshow(K); hold on; 
plot(M(1,3),M(1,4),'.','Markersize',20,'color',[1 0 0]);
plot(M(2,3),M(2,4),'.','Markersize',20,'color',[0 1 0]);
plot(M(3,3),M(3,4),'.','Markersize',20,'color',[0 1 1]);
end

