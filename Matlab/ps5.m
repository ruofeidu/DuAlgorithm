% Problem Set 5
% Bag of visual words classification
% part of this code is adapted from vlfeat software package:
% http://www.vlfeat.org/

function ps5
%% Set params
clear;

% path to vlfeat
run ./vlfeat/toolbox/vl_setup.m;
% path to liblinear 
addpath ./liblinear-1.94/matlab/;

% by default, half of images in each class is used for training
TrainRatio = 0.5;

% number of visual words in vocabulary
numWords = 600;

% ratio for each class to build dictionary
dictRatioPerClass = 0.5;

% path to Caltech 101 data
dataDir = './101_ObjectCategories/';

% method used for feature extraction, sift or filterBank
featureMethod = 'sift';

% method used for encoding, nn or le
encodingMethod = 'nn';

disp(['Feature method: ' featureMethod ', Encoding method: ' encodingMethod]);

% take a subset classes, change it to include more classes
choice = 76:80;

init_filter_bank;

%% Read data
% cls are class names
cls = dir(dataDir);
cls = {cls(choice).name};
numCls = length(cls);

% Train and Test are structure that stored training and testing data
% Train{c}{i} stores descriptors for image i in class c
% we use cell array because number of descriptors for each image might be
% different!
Train = struct;
Test = struct;

% store descriptor for each class
Train.descrs = cell(numCls,1);
Test.descrs = cell(numCls,1);

% for each class
for c = 1:numCls
    % read image files
    disp(['Class ' cls{c}]);
    imgs = dir(fullfile(dataDir,cls{c},'*.jpg'));
    
    % prepare training index for each class, do this randomly
    numImgs = length(imgs);
    idx = randperm(numImgs);
    TrainIdx = idx(1:floor(TrainRatio*numImgs));
    TestIdx = idx(floor(TrainRatio*numImgs)+1:end);
    
    imgs = cellfun(@(x)fullfile(cls{c},x),{imgs.name},'UniformOutput',false) ;
    
    % extract features for training and testing
    Train.descrs{c} = cell(length(TrainIdx),1);
    disp('Collect training descriptors...')
    for i = 1:length(TrainIdx)
        im = imread([dataDir,imgs{TrainIdx(i)}]);
        Train.descrs{c}{i} = computeFeature(im,featureMethod);% sift or filterBank
    end
    
    Test.descrs{c} = cell(length(TestIdx),1);
    disp('Collect testing descriptors...')   
    for i = 1:length(TestIdx)
        im = imread([dataDir,imgs{TestIdx(i)}]);
        Test.descrs{c}{i} = computeFeature(im,featureMethod);% sift or filterBank
    end
end   


%% Build dictionary
fprintf('Build vocabulary...\n'); 
tic;
vocab = getVocab(numCls,Train,dictRatioPerClass,numWords);
toc;

%% Encoding and representaion for each image
% Train.rep, Test.rep are representations for images, in our case
% histograms
fprintf('Build hist feature...\n'); 
tic;
Train.rep = cell(numCls,1);
Test.rep = cell(numCls,1);
for c = 1:numCls
    % for Train
    Train.rep{c} = zeros(length(Train.descrs{c}),numWords);
    for i=1:length(Train.descrs{c})% each image
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

%% Training using SVM
fprintf('SVM Trainning...\n'); 
% concat all class together
TrainData = cat(1, Train.rep{:});
TrainLabel = cell(numCls);
for c = 1 : numCls
    TrainLabel{c} = c * ones(size(Train.rep{c}, 1), 1);
end
TrainLabel = cat(1, TrainLabel{:});

% use liblinear to learn a linear SVM
[w, b, model] = trainSVM(TrainData, TrainLabel, 0.01);

%% Testing
%%%%%%%%%%%%%%%% TODO: now test your classifier on test data
fprintf('SVM Testing...\n'); 
TestData = cat(1,Test.rep{:});
TestLabel = cell(numCls);
for c = 1 : numCls
    TestLabel{c} = floor(rand()*numCls) * ones(size(Test.rep{c}, 1), 0.03);
end
TestLabel = cat(1, TestLabel{:});

do_test(Test, numCls, model);

%% Train and Test
fprintf('SVM Rushing...\n'); 
TrainData = cat(1, Train.rep{:});
TrainLabel = cell(numCls);
for c = 1 : numCls
    TrainLabel{c} = c * ones(size(Train.rep{c}, 1), 1);
end
TrainLabel = cat(1, TrainLabel{:});
TestData = cat(1,Test.rep{:});
TestLabel = cell(numCls);
for c = 1 : numCls
    TestLabel{c} = floor(rand()*numCls) * ones(size(Test.rep{c}, 1), 1);
end
TestLabel = cat(1, TestLabel{:});

best = 0;
bestc = 0; 
for c = 0.1 : 1 : 10
    [w, b, model] = trainSVM(TrainData, TrainLabel, c);
    [ label, accuracy, prob_estimates ] = do_test(Test, numCls, model);
    if (accuracy(1) > best) 
        best = accuracy(1);
        bestc = c;
    end;
end
bestc

%% Show Training Confus
data = TrainData; 
label = TrainLabel;

w = model.w';
b = -1;
% evaluate training
scores = data * w + ones(size(data,1),numCls) * b;
[~, predictLabel] = max(scores, [], 2) ;

% Compute the confusion matrix
idx = sub2ind([numCls, numCls], ...
              label', predictLabel') ;
confus = zeros(numCls) ;
confus = vl_binsum(confus, ones(size(idx)), idx) ;

% Plots
figure ; clf;
subplot(1,2,1) ;
imagesc(scores); title('Scores') ;
set(gca, 'ytick', 1:size(data,1), 'yticklabel', label) ;
subplot(1,2,2) ;
confus = confus./(repmat(sum(confus,2),[1,numCls]));
imagesc(confus) ;
title(sprintf('Confusion matrix (%.2f %% accuracy)', ...
              100 * mean(diag(confus)) )) ;
          
% Show Accuracy
disp('Accuracy:');
for c=1:numCls
    disp([cls{c} ':' num2str(100*confus(c,c)) '%']);
end

%% Show Predict Confus
data = TestData; 
label = TestLabel;
w = model.w';
b = 0;
% evaluate training
scores = data * w + ones(size(data,1),numCls) * b;
[~, predictLabel] = max(scores, [], 2) ;

% Compute the confusion matrix
idx = sub2ind([numCls, numCls], ...
              label', predictLabel') ;
confus = zeros(numCls) ;
confus = vl_binsum(confus, ones(size(idx)), idx) ;

% Plots
figure ; clf;
subplot(1,2,1) ;
imagesc(scores); title('Scores') ;
set(gca, 'ytick', 1:size(data,1), 'yticklabel', label) ;
subplot(1,2,2) ;
confus = confus./(repmat(sum(confus,2),[1,numCls]));
imagesc(confus) ;
title(sprintf('Confusion matrix (%.2f %% accuracy)', ...
              100 * mean(diag(confus)) )) ;
          
% Show Accuracy
disp('Accuracy:');
for c=1:numCls
    disp([cls{c} ':' num2str(100*confus(c,c)) '%']);
end

end
%%
function showConfus(data,label,numCls,w,b,cls)

% evaluate training
display(size(data));
display(size(w));
scores = data * w + ones(size(data,1),numCls) * b;
[~, predictLabel] = max(scores, [], 2) ;

% Compute the confusion matrix
idx = sub2ind([numCls, numCls], ...
              label', predictLabel') ;
confus = zeros(numCls) ;
confus = vl_binsum(confus, ones(size(idx)), idx) ;

% Plots
figure ; clf;
subplot(1,2,1) ;
imagesc(scores); title('Scores') ;
set(gca, 'ytick', 1:size(data,1), 'yticklabel', label) ;
subplot(1,2,2) ;
confus = confus./(repmat(sum(confus,2),[1,numCls]));
imagesc(confus) ;
title(sprintf('Confusion matrix (%.2f %% accuracy)', ...
              100 * mean(diag(confus)) )) ;
          
% Show Accuracy
disp('Accuracy:');
for c=1:numCls
    disp([cls{c} ':' num2str(100*confus(c,c)) '%']);
end

end
