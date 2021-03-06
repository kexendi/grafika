#ifndef _MAT_MATR_H
#define _MAT_MATR_H

typedef float matrix_1x4_type [4];
typedef float matrix_4x4_type [4][4];

extern float matr_sin_table[3600], matr_cos_table[3600];

extern void MatrGenerateLookupTab (void);
extern void MatrIdentity_4x4 (matrix_4x4_type p_matrix);
extern void MatrCopy_1x4 (matrix_1x4_type p_dest, matrix_1x4_type p_source);
extern void MatrCopy_4x4 (matrix_4x4_type p_dest, matrix_4x4_type p_source);
extern void MatrCopy_3x3_trsp (matrix_4x4_type p_dest, matrix_4x4_type p_source);
extern void MatrMul_1x4_4x4 (matrix_1x4_type p_matrix1, matrix_4x4_type p_matrix2, matrix_1x4_type p_matrix_res);
extern void MatrMul_4x4_4x4 (matrix_4x4_type p_matrix1, matrix_4x4_type p_matrix2, matrix_4x4_type p_matrix_res);

#endif