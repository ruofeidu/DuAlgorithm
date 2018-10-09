%% Get pixels at edge of synthesized texture.
% Input: filled matrix, window size
% Output: coordinates of unfilled neighbors.
% Author: Ruofei Du
function [ pixel_list, SSD ] = find_matches_rgb( template, valid_mask, red_patches, green_patches, blue_patches )

error_threshold = 0.1; 
[pixels_per_patch, total_patches] = size(red_patches); 

total_weight = sum(sum(valid_mask));

mask = valid_mask / total_weight;
mask_vec = mask(:)'; 
 
red = reshape(template(:, :, 1), [pixels_per_patch, 1]); 
green = reshape(template(:, :, 2), [pixels_per_patch, 1]); 
blue = reshape(template(:, :, 3), [pixels_per_patch, 1]);

red_templates = repmat(red, [1, total_patches]); 
green_templates = repmat(green, [1, total_patches]); 
blue_templates = repmat(blue, [1, total_patches]); 

red_dist =  mask_vec * (red_templates - red_patches).^2; 
green_dist = mask_vec * (green_templates - green_patches).^2 ; 
blue_dist = mask_vec * (blue_templates - blue_patches).^2; 

SSD = red_dist + green_dist + blue_dist; 
%SSD = red_dist * 0.2 + green_dist * 0.55 + blue_dist * 0.25;
%SSD = green_dist; 

pixel_list = SSD <= min(SSD) * (1 + error_threshold);  
end
