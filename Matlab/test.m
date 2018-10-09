%% Parameters
MAXD = 14; 
K = 20/255; 
dir = [-1,0;1,0;0,1;0,-1]; 

%% Unary_cost
L = imread('I1L.jpg');
R = imread('I1R.jpg'); 
dist = unary_cost(L, R, MAXD); 
subplot(1,3,1); imshow(L); 
subplot(1,3,2); imshow(R); 
subplot(1,3,3); imshow(dist(:,:,14));

%% Unary_cost2
L = zeros(20,20); L(10:11,15:16) = 255; 
R = zeros(20,20); R(10:11,13:14) = 255;
P = potts_cost(L, K); 
subplot(2,3,1); imshow(L/255); 
subplot(2,3,2); imshow(P(:,:,1)/255);
subplot(2,3,3); imshow(P(:,:,2)/255);
subplot(2,3,5); imshow(P(:,:,3)/255);
subplot(2,3,6); imshow(P(:,:,4)/255);
%%
subplot(1,3,1); imshow(L); 
subplot(1,3,2); imshow(R); 
subplot(1,3,3); imshow(dist(:,:,1));

%% Potts_cost

L = imread('I1L.jpg');
P = potts_cost(L, K); 
subplot(2,3,1); imshow(L); 
subplot(2,3,2); imshow(P(:,:,1));
subplot(2,3,3); imshow(P(:,:,2));
subplot(2,3,5); imshow(P(:,:,3));
subplot(2,3,6); imshow(P(:,:,4));

%% Potts_cost2
L = imread('T3bw.jpg');
P = potts_cost(L, K); 
subplot(2,3,1); imshow(L); 
subplot(2,3,2); imshow(P(:,:,1));
subplot(2,3,3); imshow(P(:,:,2));
subplot(2,3,5); imshow(P(:,:,3));
subplot(2,3,6); imshow(P(:,:,4));

%% initialize
L = imread('I1L.jpg');
R = imread('I1R.jpg'); 
dist = unary_cost(L, R, MAXD); 
D = initialize(dist); 
subplot(3,2,1); imshow(L); 
subplot(3,2,2); imshow(R); 
subplot(3,2,3:6); %imshow(D(:,:));
imagesc(D); 
colormap(gray); 

%% initialize2
L = imread('T3bw.jpg');
R = imread('T4bw.jpg'); 
dist = unary_cost(L, R, MAXD); 
D = initialize(dist); 
subplot(3,2,1); imshow(L); 
subplot(3,2,2); imshow(R); 
subplot(3,2,3:6); %imshow(D(:,:));
imagesc(D); 
colormap(gray); 

%% alpha beta swap 2
K = 20; 
L = imread('T3bw.jpg');
R = imread('T4bw.jpg');  
D = stereo(L, R); 
subplot(3,2,1); imshow(L); 
subplot(3,2,2); imshow(R); 
subplot(3,2,3:6); %imshow(D(:,:));
imagesc(D); 
colormap(gray); 

%%
figure;
subplot(1,2,1);
title('Alpha Beta Swap'); 
imagesc(D); 
colormap(gray); 
subplot(1,2,2); 
title('Alpha Expansion'); 
imagesc(DD); 
colormap(gray); 


%% alpha beta swap 1
tic;
L = imread('I1L.jpg');
R = imread('I1R.jpg');  
D = stereo(L, R); 

subplot(3,2,1); imshow(L); 
subplot(3,2,2); imshow(R); 
subplot(3,2,3:6); %imshow(D(:,:));
imagesc(D); 
colormap(gray); 
toc
%% alpha beta swap 1
L = imread('I1L.jpg');
R = imread('I1R.jpg');  
D = stereo(L, R, MAXD, K); 

alpha = 1; 
beta = 2; 
dist = unary_cost(L, R, MAXD); 
D = initialize(dist); 
P = potts_cost( L, K ); 

%% expansion test
K = 20; 
L = imread('T3bw.jpg');
R = imread('T4bw.jpg');   
D = stereo_expansion(L, R); 
subplot(3,2,1); imshow(L); 
subplot(3,2,2); imshow(R); 
subplot(3,2,3:6); %imshow(D(:,:));
imagesc(D); 
colormap(gray); 


%% swap test bug
L = imread('I1L.jpg');
R = imread('I1R.jpg');  
dist = unary_cost(L, R, MAXD); 
D = initialize(dist); 
P = potts_cost( L, K ); 

alpha = 1; 
beta = 2; 

[m, n] = size(D); 
dir = [-1,0;1,0;0,1;0,-1]; 

% create P matrix
[pi, pj] = find((D == alpha) | (D == beta));
pList = (D == alpha | D == beta); 
idList = zeros(size(pi)); 
nP = size(pi, 1);

% create P->T
wT = zeros(nP * 2, 1); aT = wT; bT = wT; 
nT = 0; mT = 0; mA = 0; 

for k = 1 : nP
    i = pi(k);  j = pj(k); 
    nT = nT + 1;
    idList(i,j) = nT;

    aV = 0; bV = 0;
    for d = 1 : 4
        a = i + dir(d, 1);  b = j + dir(d, 2);
        if (a<1 || a>m || b<1 || b>m) continue; end;
        if (pList(a, b) > 0)
            mA = mA + 1;
        else
            aV = aV + P(i,j,d) * (alpha ~= D(a,b));
            bV = bV + P(i,j,d) * (beta ~= D(a,b));
        end
    end
    % p->alpha
    mT = mT + 1;
    aT(mT) = idList(i,j);
    bT(mT) = 1;
    wT(mT) = dist(i,j,alpha) + aV;
    % p->beta
    mT = mT + 1;
    aT(mT) = idList(i,j);
    bT(mT) = 2;
    wT(mT) = dist(i,j,beta) + bV;    
end    
T = sparse(aT, bT, wT, nP, 2);

% create P->P, i.e. A
mA = 0;
wA = zeros(mA, 1); aA = wA; bA = wA; 

for k = 1 : nP
    i = pi(k);  j = pj(k); 
    for d = 1 : 4
        a = i + dir(d,1);   b = j + dir(d,2);
        if (a<1 || a>m || b<1 || b>n) continue; end;

        % p->p
        if (pList(a,b) > 0)
            mA = mA + 1;
            aA(mA) = idList(i, j);
            bA(mA) = idList(a, b);
            wA(mA) = P(i, j, d);
        end
    end
end
A = sparse(aA, bA, wA, nP, nP);

% max flow = min cut
[flow, labels] = maxflow(A, T);

% generate the results
res = D;
for k = 1 : nP
    i = pi(k);  j = pj(k); 
    if (labels(idList(i,j)) == 1)
       res(i,j) = alpha;
    else
       res(i,j) = beta; 
    end
end

subplot(1, 2, 1); 
imagesc(D); 
colormap(gray); 

subplot(1, 2, 2); 
imagesc(res-D); 
colormap(gray); 