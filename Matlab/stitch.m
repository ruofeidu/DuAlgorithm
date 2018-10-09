function [ res ] = stitch( J, K, A )
% stitching
%   Welcome to stitching!
tform = maketform('affine',[A', [0;0;1]]);
outer = findbounds(tform, [1, 1; size(K,2), size(K,1)]); 
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
%imshow(res);
res(deltaY+1:deltaY+size(J,1), deltaX+1:deltaX+size(J,2)) = J; 
imshow(res);
end
