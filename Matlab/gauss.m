function [ res ] = gauss( x, sigma )
    res = exp((-x.^2)/(sigma.^2)); 
end

