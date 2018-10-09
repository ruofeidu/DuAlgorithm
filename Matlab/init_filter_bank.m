function init_filter_bank
filter_size = [9,9]; 
plot_size = [3,4];
filter_num = 11;
g = zeros([filter_size, filter_num]);
sigma = [1,2,4,1,2,4,8,2,2,4,4];
para = 'replicate';

for i = 1 : 3
    g(:,:,i) = fspecial('gaussian', filter_size, sigma(i));
    %subplot(plot_size(1), plot_size(2), i); imshow(g(:,:,i), []); colormap(jet);
end

for i = 4 : 7
    g(:,:,i) = fspecial('log', filter_size, sigma(i)); 
    %subplot(plot_size(1), plot_size(2), i); imshow(g(:,:,i), []); colormap(jet);
end

% x- and y- derivatives of Guassian
gt = zeros(filter_size + 1); 
gx = zeros(filter_size + 1); 
for i = 8 : 11
    gt = fspecial('gaussian', filter_size + 1, sigma(i)); 
    if mod(i,2) == 0
        gx = imfilter( gt, [1,-1], para); 
    else
        gx = imfilter( gt, [1;-1], para);
    end
    
    g(:,:,i) = gx(1:filter_size(1), 1:filter_size(2)); 
    %subplot(plot_size(1), plot_size(2), i); imshow(g(:,:,i), []); colormap(jet);
end
end