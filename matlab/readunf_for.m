function [sparseA, aj, ja, ia, nnz, N] ...
            = readunf_for(aj_file, ja_file, ia_file)
%
% Read a CSR square matrix from unformated Fortran binary file
%
% Input
%   aj_file, ja_file, ia_file: file names for CSR sparse matrix
%
% Ouput
%      sparseA: sparse matrix in Matlab format
%   aj, ja, ia: CSR sparse matrix
%          nnz: number of nonzeros
%            N: number of row and columns
%

%% entries
%
% In aj_file, we have 
%   1. nnz = number of nonzero entires (INT*4 X 1)
%   2. aj  = nonzero entries (REAL*8 X nnz)

fid = fopen(aj_file, 'r');

length = fread(fid, 1, 'int32'); % length of record in Fortran (no use)
nnz    = fread(fid, 1, 'int32'); % number of nonzeros
aj     = fread(fid, nnz, 'double');

fclose(fid);

%% column numbers
%
% In ja_file, we have 
%   1. nnz = number of nonzero entires (INT*4 X 1)
%   2. ja  = column number for each entry (INT*4 X nnz)

fid = fopen(ja_file, 'r');

length = fread(fid, 1, 'int32'); % length of record in Fortran (no use)
nnz    = fread(fid, 1, 'int32'); % number of nonzeros
ja     = fread(fid, nnz, 'int32');

fclose(fid);

%% row numbers
%
% In ia_file, we have 
%   1. N  = number of rows (INT*4 X 1)
%   2. ia = first nonzero on each row (INT*4 X (N+1))

fid = fopen(ia_file, 'r');

length = fread(fid, 1, 'int32');
N      = fread(fid, 1, 'int32');
ia     = fread(fid, N+1, 'int32');

fclose(fid);


%% get sparese matrix in Matlab
for i=1:N
	numIA(ia(i):ia(i+1)-1)=i;
end
   
sparseA = sparse(numIA,ja,aj,N,N,nnz);

spy(sparseA);
diag(sparseA)
