num_persons = 23;
S = dir('*.jpg'); % pattern to match filenames.
clc;
 for k = 1:numel(S)
   file2read = S(k).name;
   fid = imread(file2read);
   fid = imresize(fid, [80, 80]);
   fid = rgb2gray(fid);
   fid = im2double(fid);
   imshow(fid, [])
   frontal{k} = fid; % data from file
 end
for i=1:num_persons
    expected = i;
    for j = 1:num_persons
        str = sprintf('predicted_p%d_p%d.txt',i,j);
        str  
        fileID = fopen(str, 'r');
        formatSpec = '%f';
        A = fscanf(fileID,formatSpec);
        B = A;
        B = reshape(B,80,80);
        B = transpose(B);
        predicted{i,j} = B;
    end
end
% 
% 
for i=1:num_persons
    expected = i;
    p = frontal{i};
    for j = 1:num_persons
        q = predicted{i,j};
        c = corrcoef(p,q);
        c1 = p-q;
        f(i,j) = norm(sqrt(c1 * transpose(c1)));
        results(i,j) = c(1,2);
    end
    f = f/max(max(f));
end
% for i=1:num_persons
%     for j=1:num_persons
%         results(i,j) = results(i,j) + 1 - f(i,j);
%     end
% end

[~,finalMatch] = max(results,[],2);
for i=1:23
    expected(i) = i;
end
count = 0;
for i=1:num_persons
    if expected(i) == finalMatch(i)
        count = count+1;
    end
end

true = (count/num_persons)*100
