function [ pixel_list, SSD ] = find_matches( template, valid_mask, gray_patches )

error_threshold = 0.1; 
[pixels_per_patch, total_patches] = size(gray_patches); 

total_weight = sum(sum(valid_mask));

mask = valid_mask / total_weight;
mask_vec = mask(:)'; 
 
gray = reshape(template, [pixels_per_patch, 1]); 
gray_templates = repmat(gray, [1, total_patches]); 
gray_dist =  mask_vec * (gray_templates - gray_patches).^2; 

SSD = gray_dist; 

pixel_list = SSD <= min(SSD) * (1 + error_threshold);  
end
