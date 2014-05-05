function [A,nnz,N] = readIJ(IJ_file)
%
% Read a square matrix in IJ format (ASCII)
%
% Input
%   IJ_file: file names for IJ sparse matrix
%
% Ouput
%   A: sparse matrix in Matlab format (CSR)
%

%
% In IJ_file, we have 
%   1. First line: starting and ending entry indices 
%   2. From second line: I, J, Value (I,J start from 0 not 1)

fid = fopen(IJ_file, 'r');

sizeA = fscanf(fid, '%d', [4 1]);       % read size of matrix 
A_data = fscanf(fid, '%d %d %f', inf);  % read IJ matrix

fclose(fid);

N = sizeA(2) - sizeA(1) + 1;
nnz = size(A_data,1)/3; 

IJA = reshape(A_data,3,nnz);
i = IJA(1,:)+1; j = IJA(2,:)+1; s = IJA(3,:);
A = sparse(i, j, s, N, N);
