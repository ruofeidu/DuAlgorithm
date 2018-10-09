%P1
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

threshold = 0.1;
win_size = 3; 
new_height = 15; 
new_width = 15; 
sample_patches = im2col(sample, [win_size, win_size], 'sliding'); 
[pixels_per_patch, total_patches] = size(sample_patches); 
total_weight = sum(sum(valid_mask));

mask = valid_mask; % / total_weight;
mask_vec = mask(:)'; 
gray = reshape(template, [pixels_per_patch, 1]); 
gray_templates = repmat(gray, [1, total_patches]); 
res =  mask_vec * (gray_templates - sample_patches).^2; 
pixel_list = res <= min(SSD) * (1 + error_threshold);  

%[best_matches, SSD] = find_matches(template, valid_mask, gray_patches); 