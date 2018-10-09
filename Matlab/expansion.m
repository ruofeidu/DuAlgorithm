function [ res ] = expansion(D, P, dist, alpha)
% expansion algorithm
[m, n] = size(D); 
dir = [-1,0;1,0;0,1;0,-1]; 
inf = 1e10;
nP = m * n;
nAux = 0;
nInn = 0;
    
% count P vertex
for k = 1 : m*n
    i = floor((k-1)/n)+1; 
    j = floor(mod(k-1,n))+1;
    for d = 1 : 4
        a = i + dir(d,1);   b = j + dir(d,2);
        if (a<1 || a>m || b<1 || b>n) continue; end;
        if (D(a,b) ~= D(i,j))
            if (d <= 2)
                nAux = nAux + 1;
            end
        else
            nInn = nInn + 1; 
        end
    end
end

% create P->T
nT = nP + nAux; nB = 0;
wT = zeros(nP*2 + nAux, 1);  aT = wT; bT = wT; 

for k = 1 : nP
    i = floor((k-1)/n)+1; 
    j = floor(mod(k-1,n))+1;
    
    aT(k*2-1) = k;
    bT(k*2-1) = 1;
    wT(k*2-1) = dist(i,j,alpha);

    aT(k*2) = k;
    bT(k*2) = 2;
    wT(k*2) = inf * (D(i,j) == alpha) + (D(i,j) ~= alpha) * dist(i, j, D(i,j));

    for d = 1 : 4
        a = i + dir(d,1);   b = j + dir(d,2);
        if (a<1 || a>m || b<1 || b>n) continue; end;
        if (D(a,b) ~= D(i,j))
           if (d <= 2)
                nB = nB + 1;
                aT(m*n*2+nB) = nP + nB;
                bT(m*n*2+nB) = 2;
                wT(m*n*2+nB) = P(i,j,d);
           end
        end
     end
end    
T = sparse(aT, bT, wT, nT, 2);

nA = nT; nB = 0; mA = 0; 
wA = zeros(nInn + nAux*4,1);  aA = wA; bA = wA; 

% create P->P, i.e. A
for k = 1 : m*n
    i = floor((k-1)/n)+1; 
    j = floor(mod(k-1,n))+1;
    for d = 1 : 4
        a = i + dir(d,1);   b = j + dir(d,2);
        if (a<1 || a>m || b<1 || b>n) continue; end;
        if (D(a,b)~=D(i,j))
            if (d<=2)
                nB = nB+1;
                mA = mA+1;
                aA(mA) = (i-1)*n+j;
                bA(mA) = nP + nB;
                wA(mA) = P(i,j,d)*(D(i,j)~=alpha);

                mA = mA+1;
                aA(mA) = nP + nB;
                bA(mA) = (i-1)*n+j;
                wA(mA) = P(i,j,d)*(D(i,j)~=alpha);


                mA = mA+1;
                aA(mA) = (a-1)*n+b;
                bA(mA) = nP + nB;
                wA(mA) = P(a,b,d)*(D(a,b)~=alpha);

                mA = mA+1;
                aA(mA) = nP + nB;
                bA(mA) = (a-1)*n+b;
                wA(mA) = P(a,b,d)*(D(a,b)~=alpha);
            end
        else
            mA = mA + 1;
            aA(mA) = (i-1)*n+j;
            bA(mA) = (a-1)*n+b;
            wA(mA) = P(i,j,d)*(D(i,j)~=alpha);
        end
    end
end
A = sparse(aA, bA, wA, nA, nA);
% max flow = min cut
[flow, labels] = maxflow(A, T);

% generate the results
res = D;
for k = 1 : m*n
    i = floor((k-1)/n)+1; 
    j = floor(mod(k-1,n))+1;
    if labels(k) == 1
        res(i,j) = alpha;
    end  
end

