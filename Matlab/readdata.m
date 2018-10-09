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
        %%%%%%%%%%%%%%%% TODO: write computeFeature that compute descriptor
        %%%%%%%%%%%%%%%% for given image
        Train.descrs{c}{i} = computeFeature(im,featureMethod);% sift or filterBank
    end
    
    Test.descrs{c} = cell(length(TestIdx),1);
    disp('Collect testing descriptors...')   
    for i = 1:length(TestIdx)
        im = imread([dataDir,imgs{TestIdx(i)}]);
        Test.descrs{c}{i} = computeFeature(im,featureMethod);% sift or filterBank
    end
end   