D = '/home/srija/tensorflow/-45Images/auto_output/ori';
clc;
%  S = dir('*.jpg'); % pattern to match filenames.
%  A = zeros( numel(S),128, 128 ); 
%  for k = 1:numel(S)
%    file2read = S(k).name;
%    fid = imread(file2read);
%    fid = imresize(fid, [128, 128]);
%    fid = rgb2gray(fid);
%    fid = im2double(fid);
%    imshow(fid, [])
%    frontal{k} = fid; % data from file
%  end
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





















   