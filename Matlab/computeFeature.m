function [descr] = computeFeature(im, method)
% desc_length, desc_num

if strcmp(method, 'sift')
    if (size(im,3) == 3) im = rgb2gray(im); end;
    [F, D] = vl_sift(single(im));
    descr = D'; % numDesc * 128 
    
%     imshow(im); 
%     display_sift_features(F); 
%     display(size(F)); 
%     display(size(D)); 
%     display(size(descr)); 
    
elseif strcmp(method, 'filter-bank')
    if (size(im, 3) ~= 3)
        im = cat(3, im,cat(3, im, im));
    end
    
    C = makecform('srgb2lab');
    I = applycform(im, C);
    % 17 * numDesc
    tmp = zeros(size(im, 1), size(im, 2));
    num_descr = size(im,1) * size(im, 2);
    descr = zeros(num_descr, 17);
    figure; 
    for i = 1 : 3
        for channel = 1 : 3
            tmp = imfilter(I(:,:,channel), g(:,:,i), para); 
            descr(:, i) = reshape(tmp, num_descr); 
            %subplot(3,6,(i-1)*3+channel); imshow(descr(:,:,i),[]); 
        end
    end

    for i = 4 : 7
        tmp = imfilter(I(:,:,1), g(:,:,i), para); 
        descr(:, i) = reshape(tmp, num_descr); 
        %subplot(3,6,i-3+9); imshow(descr(:,:,i),[]); 
    end

    for i = 8 : 11
        tmp = imfilter(I(:,:,1), g(:,:,i), para);
        descr(:, i) = reshape(tmp, num_descr); 
        %subplot(3,6,i-7+9+4); imshow(descr(:,:,i),[]); 
    end
end


end
