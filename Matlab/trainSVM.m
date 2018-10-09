function [ w, b, model ] = trainSVM( TrainData, TrainLabel, c )
if nargin < 3
    c = 1;
end
para = sprintf('-s 3 -c %d', c);
model = train(TrainLabel, sparse(TrainData), para);
w = model.w; 
b = model.bias;
[label, accuracy, prob_estimates] = predict(TrainLabel, sparse(TrainData), model); 

end
