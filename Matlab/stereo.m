function [ D ] = stereo(L, R)
% alpha-beta swaps
MAXD = 14; 
K = 20;  
dist = unary_cost(L, R, MAXD); 
D = initialize(dist); 
P = potts_cost( L, K ); 

% alpha beta 
    
success = 1; 
round = 0; 
while success == 1
    success = 0;
    minE = energy(D, P, dist); 
    oldE = minE; 
    for alpha = 1 : MAXD
        for beta = alpha + 1 : MAXD
           newD = swap(D, P, dist, alpha, beta); 
           newE = energy(newD, P, dist);
           if newE < minE
               success = 1; 
               D = newD; 
               minE = newE; 
           end
        end
        if (minE ~= oldE)
            fprintf('updated to %.2f from %.2f\n', minE, oldE); 
        end
    end
    round = round + 1;
    fprintf('* Round %d: arrived at %.2f\n', round, minE); 
end

end

