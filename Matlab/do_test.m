function [ label, accuracy, prob_estimates ] = do_test( Test, numCls, model )

TestData = cat(1,Test.rep{:});
TestLabel = cell(numCls);
for c = 1 : numCls
    TestLabel{c} = c * ones(size(Test.rep{c}, 1), 1);
end
TestLabel = cat(1, TestLabel{:});

[label, accuracy, prob_estimates] = predict(TestLabel, sparse(TestData), model); 

end