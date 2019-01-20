clear all;
clc;
  S = dir('*.jpg'); % pattern to match filenames.
  A = zeros( numel(S),128, 128 ); 
  for k = 1:numel(S)
    file2read = S(k).name;
    fid = imread(file2read);
    fid = imresize(fid, [128, 128]);
    fid = rgb2gray(fid);
    fid = im2double(fid);
    imshow(fid, [])
    frontal{k} = fid; % data from file
  end
% clear all;
% clc;
% for k =1:86
%    k
%    str = sprintf('res_%d.txt',k-1);
%    fileID = fopen(str, 'r');
%    formatSpec = '%f';
%    A = fscanf(fileID,formatSpec);
%    B = A;
%    B = reshape(B,128,128);
%    B = transpose(B);
%    Y{k} = B;
%    imshow(B, []);
% end
num_test = 144;
for k = 1:12
   k
   str = sprintf('res_%d.txt',k-1);
   fileID = fopen(str, 'r');
   formatSpec = '%f';
   A = fscanf(fileID,formatSpec);
   B = A;
   B = reshape(B,num_test,128*128);
   B = transpose(B);
   architecture_output{k} = B;
end


for k = 1:num_test
    k
    for l = 1:12
       A = architecture_output{l};
       B = A(:,k);
       B = reshape(B,128,128);
       B = transpose(B);
       generated{k,l} = B;
      % imshow(B, []);
    end
end
S = dir('*.jpg'); % pattern to match filenames.
clc;
 A = zeros( numel(S),128, 128 ); 
 for k = 1:numel(S)
   file2read = S(k).name;
   fid = imread(file2read);
   fid = imresize(fid, [128, 128]);
   fid = rgb2gray(fid);
   fid = im2double(fid);
   imshow(fid, [])
   frontal{k} = fid; % data from file
 end
 num_test = 144;
for i=1:num_test
    i
    for j=1:12
        P = generated{i,j};
        Q = frontal{j};
        c = corrcoef(P,Q);
        c1 = P-Q;
        f(i,j) = norm(sqrt(c1 * transpose(c1)));
        results{i,j} = c(1,2);
    end
end
f = f/max(max(f));

% for i=1:86
%     for j=1:12
%         results{i,j} = results{i,j} + 1 - f(i,j);
%     end
% end
results_cell = cell2mat(results);
[~,finalMatch] = max(results_cell,[],2);
m = 1;
for i=1:12
    for j=1:86
        k = (i-1)*86 + j;
        expected(k) = i;
    end
end
clc
count = 0;
for i=1:num_test
    if expected(i) == finalMatch(i)
        count = count+1;
    end
end

result = count/num_test)*100
