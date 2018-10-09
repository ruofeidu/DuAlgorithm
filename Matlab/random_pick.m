%% Random pick valid pixels from matches.
% Input: best matches
% Output: randomly picked pixel
% Author: Ruofei Du
function res = random_pick( best_matches )
    matches = find(best_matches);                   % get nonzero elements
    res = matches(ceil(rand() * length(matches)));  % get a pixel from the list
end