#include <math.h>
#include "mat_matr.h"

float matr_sin_table[3600], matr_cos_table[3600];


void MatrGenerateLookupTab (void)
{
   int i;
   for(i=0; i<3600; i++)
   {
      matr_sin_table[i]=(float)sin(i*3.1415/1800);
      matr_cos_table[i]=(float)cos(i*3.1415/1800); 
   }    
}


void MatrIdentity_4x4 (matrix_4x4_type p_matrix)
{
	int j,k;

	for (j=0;j<4;j++)
	{
		for (k=0;k<4;k++)
		{
			if (j==k)
				p_matrix[j][k]=1;
			else
				p_matrix[j][k]=0;
		}
	}
}


void MatrCopy_1x4 (matrix_1x4_type p_dest, matrix_1x4_type p_source)
{
   int i;

   for(i=0;i<4;i++)
   {
        p_dest[i]=p_source[i];
   }
}



void MatrCopy_4x4 (matrix_4x4_type p_dest, matrix_4x4_type p_source)
{
   int j,k;
   for(j=0;j<4;j++)
      for(k=0;k<4;k++)
        p_dest[j][k]=p_source[j][k];
}

void MatrCopy_3x3_trsp (matrix_4x4_type p_dest, matrix_4x4_type p_source)
{
   int j,k;

   for(j=0;j<3;j++)
      for(k=0;k<3;k++)
        p_dest[j][k]=p_source[k][j];
}

void MatrMul_1x4_4x4 (matrix_1x4_type p_matrix1, matrix_4x4_type p_matrix2, matrix_1x4_type p_matrix_res)
{
    int j,k;
    float l_sum;

    for (j=0;j<4;j++)
    {
        l_sum=0;
        for(k=0;k<4;k++)
            l_sum+=p_matrix1[k]*p_matrix2[k][j];
        p_matrix_res[j]=l_sum;
    }
}

void MatrMul_4x4_4x4 (matrix_4x4_type p_matrix1, matrix_4x4_type p_matrix2, matrix_4x4_type p_matrix_res)
{
    int i,j,k;
    float l_sum;

    for (i=0;i<4;i++)
    {
        for (j=0;j<4;j++)
        {
            l_sum=0;
            for(k=0;k<4;k++)
                l_sum+=p_matrix1[i][k]*p_matrix2[k][j];
            p_matrix_res[i][j]=l_sum;
        }
    }
}

