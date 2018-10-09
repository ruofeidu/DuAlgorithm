function [histo] = encoding(vocab, desc, numWords, encodingMethod)

%desc = Train.descrs{1}{1};
histo = zeros(1, numWords); 
[desc_num, desc_length] = size(desc);

if strcmp(encodingMethod, 'nn')
    kdtree = vl_kdtreebuild(double(vocab));
    [index, ~] = vl_kdtreequery(kdtree, double(vocab), double(desc'));
    for i = 1 : size(index, 2)
        histo(index(i)) = histo(index(i)) + 1.0;
    end

%   Brute-Force Nearest Neighbour
% 
%     [~, desc_num] = size(desc);
%     histo = double(zeros(1,numWords));
%     for i = 1 : desc_num
%         vec = double(desc(:, i));
%         min_dist = sum((vec - vocab(:,1)).^2);
%         nearest = 1;
%         for j = 2 : numWords
%             dist = sum((vec - vocab(:,j)) .^ 2);
%             if (dist < min_dist) 
%                 min_dist = dist;
%                 nearest = j;
%             end
%         end
%         histo(nearest) = histo(nearest) + 1.0;
%     end

histo = histo ./ max(histo);
%histo = (double(histo)) ./ double(sum(histo)); 
    
elseif strcmp(encodingMethod, 'le')
    for i = 1 : desc_num
        vec = double(desc(i, :)'); %desc_length
        % length_desc, num_words
        for j = 1 : numWords
            total = sum((vec - vocab(:,j)).^2);
            histo(j) = histo(j) + 1.0 / total;
        end
    end
    histo = double(histo);
    histo = (histo-min(histo)) / (max(histo)-min(histo));
end
