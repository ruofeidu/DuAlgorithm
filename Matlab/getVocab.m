function [ vocab ] = getVocab(numCls, Train, dictRatioPerClass, numWords);

dictRatioPerClass = 1; 
%[desc_num, desc_length] = size(desc);
des_length = size(Train.descrs{1}{1},2); 
des_num = 0; 
for c = 1:numCls
    for i = 1:floor(size(Train.descrs{c})*dictRatioPerClass)
        des_num = des_num + size(Train.descrs{c}{i}, 1); 
    end
end

all_des = zeros(des_num, des_length); 
des_num = 1; 
for c = 1:numCls
    for i = 1:floor(size(Train.descrs{c})*dictRatioPerClass)
        all_des(des_num:des_num+size(Train.descrs{c}{i}, 1)-1,:) = Train.descrs{c}{i};
        des_num = des_num + size(Train.descrs{c}{i}, 1); 
    end
end

vocab = vl_kmeans(all_des', numWords); 
%vocab = kmeans(all_des, numWords); 

end

