%% FindMathces for Problem 2
% Input: sample, template, mask
% Output: matched_pixels
% Author: Ruofei Du
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

valid_mask = [
1,1,1; 
1,1,0; 
1,1,0];

error_threshold = 0.1; 
[pixels_per_patch, total_patches] = size(gray_patches); 

total_weight = sum(sum(valid_mask));

mask = valid_mask / total_weight;
mask_vec = mask(:)'; 
 
gray = reshape(template, [pixels_per_patch, 1]); 
gray_templates = repmat(gray, [1, total_patches]); 
SSD =  mask_vec * (gray_templates - gray_patches).^2; 

pixel_list = SSD <= min(SSD) * (1 + error_threshold);  
pixel_matrix = reshape(pixel_list, [7 7]); 
