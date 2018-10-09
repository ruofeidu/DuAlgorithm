%% everything
fprintf('Build vocabulary...\n'); 
tic;

dictRatioPerClass = 1; 

des_length = size(Train.descrs{1}{1},2); 
%vocab = zeros(numWords, des_length); 
des_num = 0; 
for c = 1:numCls
    for i = 1:floor(size(Train.descrs{c},1)*dictRatioPerClass)
        des_num = des_num + size(Train.descrs{c}{i}, 1); 
    end
end
%TODO RANDOM
all_des = zeros(des_num, des_length); 
des_num = 1; 
for c = 1:numCls
    for i = 1:floor(size(Train.descrs{c})*dictRatioPerClass)
        all_des(des_num:des_num+size(Train.descrs{c}{i}, 1)-1,:) = Train.descrs{c}{i};
        des_num = des_num + size(Train.descrs{c}{i}, 1); 
    end
end

vocab = vl_kmeans(all_des', numWords); 
% length_desc, num_words

toc;

fprintf('Build hist feature...\n'); 
tic;
Train.rep = cell(numCls,1);
Test.rep = cell(numCls,1);
for c = 1:numCls
    % for Train
    Train.rep{c} = zeros(length(Train.descrs{c}),numWords);
    for i = 1 : length(Train.descrs{c})% each image
    % write encoding() that calculate histogram
    % representation of an image given leared
    % vocabulary/dictionary
        Train.rep{c}(i,:) = encoding(vocab,Train.descrs{c}{i},numWords,encodingMethod);% nearest neighbor or local encoding
    end
    % for Test
    Test.rep{c} = zeros(length(Test.descrs{c}),numWords);    
    for i=1:length(Test.descrs{c})
        Test.rep{c}(i,:) = encoding(vocab,Test.descrs{c}{i},numWords,encodingMethod);% nearest neighbor or local encoding
    end
end
toc;
fprintf('SVM Trainning...\n'); 
% concat all class together
TrainData = cat(1, Train.rep{:});
TrainLabel = cell(numCls);
for c = 1 : numCls
    TrainLabel{c} = c * ones(size(Train.rep{c}, 1), 1);
end
TrainLabel = cat(1, TrainLabel{:});

% use liblinear to learn a linear SVM
[w, b, model] = trainSVM(TrainData, TrainLabel, numCls, cls);

fprintf('SVM Testing...\n'); 
do_test(Test, numCls, model);
