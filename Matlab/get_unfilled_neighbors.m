%% Get pixels at edge of synthesized texture.
% Input: filled matrix, window size
% Output: coordinates of unfilled neighbors.
% Author: Ruofei Du
function [ pixel_rows, pixel_cols ] = get_unfilled_neighbors( filled, win_size )

% get the border without for loops
border = bwmorph(filled, 'dilate') - filled; 
[pixel_rows, pixel_cols] = find(border);
len = length(pixel_rows); 

% the list is randomly permuted
rand_array = randperm(len); 
pixel_rows = pixel_rows(rand_array); 
pixel_cols = pixel_cols(rand_array); 

% and then sorted by decreasing number of filled neighbor pixels   
filled_sums = colfilt(filled, [win_size, win_size], 'sliding', @sum); 
num_filled_neighbors = filled_sums( sub2ind(size(filled), pixel_rows, pixel_cols) ); 
[~, sort_indices] = sort(num_filled_neighbors, 1, 'descend');

pixel_rows = pixel_rows(sort_indices); 
pixel_cols = pixel_cols(sort_indices); 

end

