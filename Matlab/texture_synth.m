%% Texture Synthesis.
% Input: sample image, window size, new height, new width, threshold, debug
% Output: coordinates of unfilled neighbors.
% Author: Ruofei Du
%function res = texture_synth( sample, win_size, new_height, new_width, threshold, debug )
debug = true; 
hsv = false;
lab = false; 

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

    sample = [
    0,0,0,1,1,1,0,0,0,1,1,1; 
    0,0,0,1,1,1,0,0,0,1,1,1; 
    0,0,0,1,1,1,0,0,0,1,1,1; 
    1,1,1,0,0,0,1,1,1,0,0,0; 
    1,1,1,0,0,0,1,1,1,0,0,0; 
    1,1,1,0,0,0,1,1,1,0,0,0; 
    0,0,0,1,1,1,0,0,0,1,1,1; 
    0,0,0,1,1,1,0,0,0,1,1,1; 
    0,0,0,1,1,1,0,0,0,1,1,1;
    1,1,1,0,0,0,1,1,1,0,0,0; 
    1,1,1,0,0,0,1,1,1,0,0,0; 
    1,1,1,0,0,0,1,1,1,0,0,0; 
    ];

    %sample = im2double(imread('brickbw.jpg')); 
    %sample = im2double(imread('slope.jpg')); 
    %sample = im2double(imread('slopec.jpg')); 
    %sample = im2double(imread('word.jpg')); 
    sample = im2double(imread('161.jpg'));
    %sample = im2double(imread('wordc.jpg'));
    %sample = im2double(imread('rainbow.jpeg'));
    %sample = im2double(imread('strawberry.jpg'));
    %sample = im2double(imread('chess.jpg')); 
    sample = im2double(imread('fire.jpg'));
    
    template = [
    1,0,0;
    0,1,1; 
    0,1,1];

    mask = [
    1,1,1; 
    1,1,0; 
    1,1,0];
    
    threshold = 0.1;
    win_size = 15; 
    new_height = 201; 
    new_width = 201; 
end

% Initialization

sample = double(sample);
if hsv
    sample = rgb2hsv(sample);
elseif lab
    sample = rgb2lab(sample); 
end

[height, width, channels] = size(sample);
win_del_size = [height - win_size + 1, width - win_size + 1];
win_half = (win_size - 1) / 2; 
total_pixels = new_height * new_width; 
res = zeros(new_height, new_width, channels); 

% [winsize * winsize, (height - winsize + 1) * (width - winsize + 1)]
if channels == 1
    gray_patches = im2col(sample, [win_size, win_size], 'sliding'); 
elseif channels == 3
    red_patches = im2col(sample(:, :, 1), [win_size, win_size], 'sliding'); 
    green_patches = im2col(sample(:, :, 2), [win_size, win_size], 'sliding'); 
    blue_patches = im2col(sample(:, :, 3), [win_size, win_size], 'sliding'); 
end

% initial res with a random 3*3 seed patch from the sample
rand_row = ceil( rand() * (height - 2));
rand_col = ceil( rand() * (width - 2));
seed_size = 3; 
seed_rows = ceil(new_height / 2) : ceil(new_height / 2) + seed_size - 1; 
seed_cols = ceil(new_width / 2) : ceil(new_width / 2 ) + seed_size - 1; 
res(seed_rows, seed_cols, :) = sample( rand_row : rand_row + seed_size - 1, rand_col : rand_col + seed_size - 1, :); 

total_filled = seed_size * seed_size; 
filled = false([new_height, new_width]); 
filled(seed_rows, seed_cols) = true([3, 3]); 

total_skipped = 0; 

while total_filled < total_pixels
    progress = false; 
    
    [pixel_rows, pixel_cols] = get_unfilled_neighbors(filled, win_size); 
    
    for i = 1 : length(pixel_rows)
        % get template and valid mask
        pixel_row = pixel_rows(i); 
        pixel_col = pixel_cols(i); 
        
        row_range = pixel_row - win_half : pixel_row + win_half; 
        col_range = pixel_col - win_half : pixel_col + win_half; 
        
        dead_rows = row_range < 1 | row_range > new_height; 
        dead_cols = col_range < 1 | col_range > new_width; 
        
        if sum(dead_rows) + sum(dead_cols) > 0
            safe_rows = row_range(~dead_rows);
            safe_cols = col_range(~dead_cols); 
            
            template = zeros(win_size, win_size, channels); 
            template(~dead_rows, ~dead_cols, :) = res( safe_rows, safe_cols, :); 
            
            valid_mask = false(win_size, win_size); 
            valid_mask(~dead_rows, ~dead_cols) = filled(safe_rows, safe_cols); 
            
        else
            template = res(row_range, col_range, :); 
            valid_mask = filled(row_range, col_range); 
        end
        
        % find best matches
        if channels == 1
            [best_matches, SSD] = find_matches(template, valid_mask, gray_patches); 
        elseif channels == 3
            [best_matches, SSD] = find_matches_rgb(template, valid_mask, red_patches, green_patches, blue_patches);
        end
        
        match_indices = random_pick(best_matches); 
        match_error = SSD(match_indices); 
        
        % if error is within threshold add
        if match_error < threshold
           [match_row, match_col] = ind2sub(win_del_size, match_indices); 
           
           match_row = match_row + win_half; 
           match_col = match_col + win_half; 
           
           res(pixel_row, pixel_col, :) = sample(match_row, match_col, :); 
           
           filled(pixel_row, pixel_col) = true; 
           total_filled = total_filled + 1; 
           progress = true; 
        else
           total_skipped = total_skipped + 1; 
        end
    end
    
    fprintf('Percentage: %d / %d\n', total_filled, total_pixels); 

    if hsv
        aa = hsv2rgb(sample);
        bb = hsv2rgb(res);
        subplot(1,2,1); imshow(aa); 
        subplot(1,2,2); imshow(bb);
    elseif lab
        aa = lab2rgb(sample);
        bb = lab2rgb(res);
        subplot(1,2,1); imshow(aa); 
        subplot(1,2,2); imshow(bb);
    else
        subplot(1,2,1); imshow(sample); 
        subplot(1,2,2); imshow(res); 
    end
    %subplot(1,3,3); imshow(filled); 
    if ~progress 
        threshold = threshold * 1.1;
        fprintf('Current threshold: %d\n', threshold); 
    end
end

%end