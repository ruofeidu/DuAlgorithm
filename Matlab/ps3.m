function o = ps3(pnum)
switch pnum
    case 1
        I = single(zeros(100,100));
        I(40:60,40:60) = 255;
	  % Testing SIFT with a white square on a black background.
        [F, D] = vl_sift(I);
        figure;
        imshow(I);
        display_sift_features(F);
        
	  % Testing SIFT with images we provide.
        J = imread('LR1bw.jpg');
        [F2, D2] = vl_sift(single(J));
        figure;
        imshow(J);
        display_sift_features(F2);
        
        K = imread('LR2bw.jpg');
        [F3, D3] = vl_sift(single(K));
        figure;
        imshow(K);
        display_sift_features(F3);
        
    case 2
        J = imread('LR1bw.jpg');
        [F2, D2] = vl_sift(single(J));
        K = imread('LR2bw.jpg');
        [F3, D3] = vl_sift(single(K));
        M = find_best_match(F2, D2, F3, D3);
	  % You need to write find_best_match.
	  % M should be an nx5 matrix.  n = size(F3,2).
	  % Row i of M shows a match between the i'th feature in F3
	  % and the best matching feature in F2. 
        show_3_best(M, J, K);
	  % You also need to write show_3_best.  display_sift_features may help.
        
    case 3
        p1 = rand(2,3);
        p2 = rand(2,3);
        A = affine_transformation(p1,p2);
	  % Write affine_transformation, to produce A so that the 
	  % expression below evaluates to a matrix that is almost 0.
        p2 - A*[p1; ones(1,3)]
        
    case 4
        p1 = 100*rand(2,8);
        A = 100*rand(2,3);
        p2 = A*[p1; ones(1,8)];
	  % Points in p2 match p1 perfectly using A.
        p1 = [p1, 100*rand(2,16)];
        p2 = [p2, 100*rand(2,16)];
	  % Now we've added some noisy points that don't match.
        M = [p1', p2', ones(24,1)];
        Ares = ransac(M);
	  % Write ransac to find the affine transformation that 
	  % matches the most points in M.
        A, Ares
	  % A and Ares should be the same, since the best affine
	  % transformation will match the first 8 points of p1 and p2.
    case 5
        J = imread('LR1bw.jpg');
        K = imread('LR2bw.jpg');
        A1 = translate100;
        Is1 = stitch_blend(J, K, A1);
        figure;
        imshow(uint8(Is1));
        
         A2 = trs;
         Is2 = stitch_blend(J, K, A2);
         figure;
         imshow(uint8(Is2));
    case 6
        J = imread('LR1bw.jpg');
        K = imread('LR2bw.jpg');
        Im = mosaic(J, K);
	  % And put everything together in mosaic.
        figure;
        subplot(2,1,1); 
        imshow(uint8(Im));
        subplot(2,2,3); 
        imshow(J); 
        subplot(2,2,4); 
        imshow(K);
        
    case 7
        J = imread('photo3.jpg');
        K = imread('photo4.jpg');
	    Im = mosaic(J, K);
        figure;
        subplot(2,1,1); 
        imshow(uint8(Im));
        subplot(2,2,3); 
        imshow(J); 
        subplot(2,2,4); 
        imshow(K);
    case 8
        J1 = imread('lake3.jpg');
        K1 = imread('lake4.jpg');
	    J = rgb2gray(J1);
        K = rgb2gray(K1); 
        Im = mosaic(J, K);
        figure;
        subplot(2,1,1); 
        imshow(uint8(Im));
        subplot(2,2,3); 
        imshow(J); 
        subplot(2,2,4); 
        imshow(K);
        
     case 11
        J1 = imread('IMAGLL.jpg');
        K1 = imread('IMAGRR.jpg');
	    J = rgb2gray(J1);
        K = rgb2gray(K1); 
        Im = mosaic(J, K);
        figure;
        subplot(2,1,1); 
        imshow(uint8(Im));
        subplot(2,2,3); 
        imshow(J); 
        subplot(2,2,4); 
        imshow(K);
    case 9
        J = imread('LR1bw.jpg');
        K = imread('LR2bw.jpg');
        A =[
    0.9946    0.0036   64.8746;
    0.0028    0.9998    3.1896];
        Is1 = stitch_average(J, K, A);
        figure;
        imshow(uint8(Is1));
        
    case 10
         J1 = imread('lake3.jpg');
        K1 = imread('lake4.jpg');
	    J = rgb2gray(J1);
        K = rgb2gray(K1); 
        A =[
            1.0416   -0.0180 -113.8988;
            0.0349    1.0111   -8.0913];
        Im = stitch_blend(J, K, A);
        figure;
        figure;
        subplot(2,1,1); 
        imshow(uint8(Im));
        subplot(2,2,3); 
        imshow(J); 
        subplot(2,2,4); 
        imshow(K);
        
    case 12
         J1 = imread('hcil3.jpg');
        K1 = imread('hcil4.jpg');
	    J = rgb2gray(J1);
        K = rgb2gray(K1); 
        Im = mosaic(J, K);
        figure;
        subplot(2,1,1); 
        imshow(uint8(Im));
        subplot(2,2,3); 
        imshow(J); 
        subplot(2,2,4); 
        imshow(K);
end
o = 1;

function o = display_sift_features(F, m)
% F is a set of SIFT features.  You will want to have already
% displayed an image in a figure, using imshow.
% Note that m can be used to change the color or type of marker
% used.
if nargin < 2
    m = 'ro';
end
hold on
for i = 1:size(F,2)
    plot(F(1,i), F(2,i), m, 'MarkerSize', F(3,i));
end
hold off
o = 1;

