/*-- I/O for Sparse Matrix  -----------------------------*/
#include <stdio.h>
#include <stdlib.h>


/*-- Read a vector from a file  -------------------------*/

double * Read_Double_Vector( const char *filename, int N )
{
  FILE      *file;
  double    *vec = NULL;
  int       i, length;

  if ( N <= 0 ) {
    printf("Error: Wrong number of entries!\n"); 
  }
  
  vec = (double *) calloc( N, sizeof(double) );

  file = fopen(filename, "rb");
  if ( file != NULL ) {
    fread( &length, sizeof(int), 1, file );
    fread( vec,  sizeof(double), N, file );
    fread( &length, sizeof(int), 1, file );
    fclose(file);
  }
  else {
    printf("\nWarning: No vector information in %s.\n", filename);
    for (i=0;i<N;i++) vec[i] = 0.0;
  }
    
  return(vec);
}

/*--  Read Sparse Aj  --------------------------------------*/

double * Read_Sparse_Aj( const char *file_Aj )
{
  FILE	  *file;
  double  *vec = NULL;
  int     length, i, nnz;

  file = fopen(file_Aj, "rb");
  if ( file != NULL ) {
    fread( &length, sizeof(int), 1, file );
    fread( &nnz,    sizeof(int), 1, file );
    vec = (double *) calloc( nnz, sizeof(double) );
    fread( vec, sizeof(double), nnz, file);
    fread( &length, sizeof(int), 1, file );
    fclose(file);
  }
  else {
    printf("\nError: No matrix information -- Aj!\n"); 
  }
  
  return(vec);
}


/*--  Read Sparse jcol  ------------------------------------*/

int * Read_Sparse_ja( const char *file_ja )
{
  FILE	  *file;
  int     *vec = NULL;
  int     length, i, nnz;

  file = fopen(file_ja, "rb");
  if ( file != NULL ) {
    fread( &length, sizeof(int), 1, file );
    fread( &nnz,    sizeof(int), 1, file );
    vec = (int *) calloc( nnz, sizeof(int) );
    fread( vec, sizeof(int), nnz, file);
    fread( &length, sizeof(int), 1, file );
    fclose(file);
  }
  else {
    printf("\nError: No matrix information -- ja!\n"); 
  }

  /* Change index: starting from 0 if start with 1 (for compatibility)*/
  if (vec[0] > 0) {
    for ( i = 0; i < nnz; i++ ) vec[i] = vec[i] - 1;
  }

  return(vec);
}


/*--  Read Sparse numcol  ----------------------------------*/

int * Read_Sparse_ia( const char *file_ia, int *N )
{
  FILE	  *file;
  int     *vec = NULL;
  int     length, i;

  file = fopen(file_ia, "rb");
  if ( file != NULL ) {
    fread( &length, sizeof(int), 1, file );
    fread( N,       sizeof(int), 1, file );
    vec = (int *) calloc( *N+1, sizeof(int) );
    fread( vec, sizeof(int), *N+1, file);
    fread( &length, sizeof(int), 1, file );
    fclose(file);
  }
  else {
    printf("\nError: No matrix information -- ia!"); 
  }

  /* Change index: starting from 0 if start with 1 (for compatibility)*/
  if (vec[0] > 0) {
    for ( i = 0; i <= *N; i++ ) vec[i] = vec[i] - 1;
  }

  return(vec);
}
