% Check Sparse Matrix
%
% last modified by Chensong Zhang
% on Oct/10/2008

clear all; close all;

%% read sparse matrix in CSR format

[aj, ja, ia, nnz, N] = readunf_for('aj.CSR', 'ja.CSR', 'ia.CSR');


%% read sparse matrix in IJ format

[A,nnz,N] = readIJ('A.IJ'); spy(A);