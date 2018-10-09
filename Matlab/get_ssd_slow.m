%% SSD Calculator
% Input: sample, template, mask
% Output: SSD
% Author: Ruofei Du
function [ res ] = get_ssd_slow( sample, template, mask, debug )
if (nargin < 4) debug = false; end;
if debug
    sample = [
    1,1,1,0,0,0,1,1,1; 
    1,1,1,0,0,0,1,1,1; 
    1,1,1,0,0,0,1,1,1; 
    0,0,0,1,1,1,0,0,0; 
    0,0,0,1,1,1,0,0,0; 
    0,0,0,1,1,1,0,0,0; 
    1,1,1,0,0,0,1,1,1; 
    1,1,1,0,0,0,1,1,1; 
    1,1,1,0,0,0,1,1,1];

    template = [
    1,0,0;
    0,1,1; 
    0,1,1];

    mask = [
    1,1,1; 
    1,1,0; 
    1,1,0];
end

sample = double(sample);
[height, width] = size(sample);
win_size = size(template, 1); 
win_half = (win_size - 1) / 2;
threshold = 0.1; 

res = zeros(height, width); 
n = height * width; 
m = size(template,1) * size(template,2); 

valid_mask = mask; 
total_weight = sum(sum(valid_mask)); 

for x = 1 : n
    i = floor((x-1) / width) + 1;
    j = mod((x-1), height) + 1; 
    for y = 1 : m
        ii = floor((y-1) / win_size) + 1;
        jj = mod(y-1, win_size) + 1; 
        if (i-win_half-1+ii > 0 && j-win_half-1+jj > 0 && i-win_half-1+ii < height && j-win_half-1+jj < width)
            dist = (template(ii, jj) - sample(i-win_half-1+ii, j-win_half-1+jj))^2;
            res(i, j) = res(i, j) + dist * mask(ii, jj);
        end
    end
    res(i, j) = res(i, j) / total_weight; 
end 
%pixel_list = res(res <= min(res) * (1 + error_threshold));  
%cord = im2col(sample, [h, w]);
%pixelList = cord(res<=min(res)*(1 + threshold));

end