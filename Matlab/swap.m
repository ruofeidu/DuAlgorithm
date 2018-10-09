function [ res ] = swap(D, P, dist, alpha, beta)
% swap algorithm
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
    wT(mT) = dist(i, j, alpha) + aV;
    % p->beta
    mT = mT + 1;
    aT(mT) = idList(i,j);
    bT(mT) = 2;
    wT(mT) = dist(i, j, beta) + bV;    
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