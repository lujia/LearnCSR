/*---------------------------------------------------
 Test: reading sparse matrix in CSR format 

 file written in Fortran binary form
  
 by Chensong Zhang
 
 Oct/02/2008
 ----------------------------------------------------*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double * Read_Double_Vector( const char *filename, int N );
double * Read_Sparse_Aj( const char *file_Aj );
int    * Read_Sparse_ja( const char *file_ja );
int    * Read_Sparse_ia( const char *file_ia, int *N );

/*----  Main Program  -----------------------------------------*/ 
int main (int argc, char *argv[])
{

  /* Local information for matrices and vectors */

  int     N;
  int     *ia, *ja;  
  double  *Aj;

  /*-------------------------------------------------------------*/
  /*   Step 1. Read CSR matrix written as Fortran binary file    */
  /*-------------------------------------------------------------*/
  
  /* Read coefficient matrix in CSR format (Fortran binary file)
     Note: ja starts from 0 to nnz */
  Aj = Read_Sparse_Aj( "aj.CSR" );
  ja = Read_Sparse_ja( "ja.CSR" );
  ia = Read_Sparse_ia( "ia.CSR", &N );
  
  return(0);
}
