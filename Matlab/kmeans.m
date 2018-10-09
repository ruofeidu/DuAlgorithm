function vocab = kmeans(all_des, num_words)
[des_num, des_length] = size(all_des);
vocab = ones(num_words, des_length+1); 
all_des(:,des_length+1) = 0; 
for i = 1 : num_words
    rand_pos = i * floor(des_num/num_words) - floor(rand(1,1)*(des_num/num_words));
    vocab(i,:) = all_des(rand_pos,:);
end

best = 1e8; flag = true; step = 1;
dist = zeros(des_num, num_words);
while flag
    flag = false; step = step + 1;
    % get the dist map
    for i = 1 : des_num
        for j = 1 : num_words
            dist(i, j) = sqrt(sum((all_des(i, :) - vocab(j, :)).^2)); 
        end
        % all_des(i, des_length+1) = min(dist(i,:)); 
        [~, y] = find(dist(i, :) == min(dist(i, :)));
        same_precision = size(find(y == all_des(i, des_length+1)), 2); 
        if same_precision == 0
            flag = true; 
            all_des(i, des_length+1) = y(1,1); 
        else
            continue; 
        end
    end
    
    for j = 1 : num_words
        totalA = 0;
        [r, c] = find(all_des(:, des_length+1) == j);
        vocab(j, :) = mean(all_des(r, :), 1); 
        for x = 1 : length(r)
            totalA = totalA + sqrt(sum((all_des(r(x),:) - vocab(j, :))) .^ 2);
        end
        center_sum(1, j) = totalA;
    end
    if sum(center_sum(1,:)) > best
        break;
    end
    best = sum(center_sum(1, :)); 
end
vocab = vocab(:, 1:des_length)';

end
