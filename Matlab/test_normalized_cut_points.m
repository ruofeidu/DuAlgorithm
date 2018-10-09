function test_normalized_cut_points()
p1 = 2.5*rand(2,20);
p2 = 2.5*rand(2,20) + repmat([3;2], 1, 20);
p = [p1, p2];
q = normalized_cut_cont_points(p, 2.5);
msize = 10+20*(q-min(q))/(max(q)-min(q));
figure;
hold on;
for i = 1:size(p,2)
    plot(p(1,i), p(2,i), '.', 'MarkerSize', msize(i));
end

group = normalized_cut_points(p, 2.5);
figure;
hold on
plot(p(1,group), p(2,group), '.r');
plot(p(1,~group), p(2, ~group), '.b');
