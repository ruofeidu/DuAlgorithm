function [ res ] = stitch_blend( J, K, A )
% stitching
%   Welcome to stitching!
tform = maketform('affine',[A', [0;0;1]]);
outer = findbounds(tform, [1, 1; size(K,2), size(K,1)]); 
outer(1,1) = floor(outer(1,1));
outer(1,2) = floor(outer(1,2));
outer(2,1) = ceil(outer(2,1));
outer(2,2) = ceil(outer(2,2));

if (outer(1,1) < 0) 
    deltaX = -outer(1,1)+1; 
    xdata = [outer(1,1), outer(2,1)+deltaX]; 
else
    deltaX = 0; 
    xdata = [1, outer(2,1)];
end;

if (outer(1,2) < 0) 
    deltaY = -outer(1,2)+1;
    ydata = [outer(1,2), outer(2,2)+deltaY];
else
    deltaY = 0;
    ydata = [1, outer(2,2)]; 
end;

res = imtransform(K, tform, 'XData', xdata, 'YData', ydata); 

% Make Mask
cx = ceil(size(K,2) / 2); 
cy = ceil(size(K,1) / 2); 
p2 = A * [cx; cy; 1];
cx = p2(1); 
cy = p2(2);

KW = zeros(size(res,1), size(res,2)); 

for i = 1 : size(res,1)
    for j = 1 : size(res,2)
        if res(i,j) > 0
            KW(i,j) = blend_dist(j,i,cx,cy);
        end
    end
end

KW = KW ./ max(max(KW));
JW = blend_map(size(J,1), size(J,2));
JW = JW ./ max(max(JW));
%imshow(KW); 
%figure; 
% Boundary Threshold
threshold = 0.4;

% Color Blending Start
for y = deltaY+1 : deltaY+size(J,1)-1
    for x = deltaX+1 : deltaX+size(J,2)-1
        jy = y - deltaY;
        jx = x - deltaX;
        if res(y,x) < 1e-6 || abs(KW(y,x) - 1) < threshold
           res(y,x) = J(jy, jx); 
        else
           qj = KW(y,x) / (KW(y,x) + JW(jy,jx));
           qk = JW(jy,jx) / (KW(y,x) + JW(jy,jx));
           res(y,x) = qj * J(jy, jx) + qk * res(y, x); 
        end
    end
end
imshow(res);
end
