#include "camera.h"
#include "mat_matr.h"

camera_type camera;

void CamTranslate (float p_x,float p_y,float p_z)
{
    camera.matrix[3][0]+=p_x;
    camera.matrix[3][1]+=p_y;
    camera.matrix[3][2]+=p_z;
}

void CamTranslateW (float p_x,float p_y,float p_z)
{
    matrix_4x4_type l_matrix, l_res;
    MatrIdentity_4x4(l_matrix); 
	l_matrix[3][0]=p_x;
	l_matrix[3][1]=p_y;
	l_matrix[3][2]=p_z;
	MatrMul_4x4_4x4(l_matrix,camera.matrix,l_res);
	MatrCopy_4x4(camera.matrix,l_res);
}


void CamRotate(int p_angle_x,int p_angle_y,int p_angle_z)
{
    matrix_4x4_type l_matrix, l_res;
	
	if (p_angle_x<0) p_angle_x=3600+p_angle_x;
    if (p_angle_y<0) p_angle_y=3600+p_angle_y;  
    if (p_angle_z<0) p_angle_z=3600+p_angle_z;
    if (p_angle_x<0 || p_angle_x>3600) p_angle_x=0;
    if (p_angle_y<0 || p_angle_y>3600) p_angle_y=0;  
    if (p_angle_z<0 || p_angle_z>3600) p_angle_z=0;

    if (p_angle_x)
    {
        MatrIdentity_4x4(l_matrix);
        l_matrix[1][1]=(matr_cos_table[p_angle_x]);
        l_matrix[1][2]=(matr_sin_table[p_angle_x]);
        l_matrix[2][1]=(-matr_sin_table[p_angle_x]);
        l_matrix[2][2]=(matr_cos_table[p_angle_x]);
	    MatrMul_4x4_4x4(camera.matrix,l_matrix,l_res);
		MatrCopy_4x4(camera.matrix,l_res);
    }
    if (p_angle_y)
    {
        MatrIdentity_4x4(l_matrix);
        l_matrix[0][0]=(matr_cos_table[p_angle_y]);
        l_matrix[0][2]=(-matr_sin_table[p_angle_y]);
        l_matrix[2][0]=(matr_sin_table[p_angle_y]);
        l_matrix[2][2]=(matr_cos_table[p_angle_y]);
		MatrMul_4x4_4x4(camera.matrix,l_matrix,l_res);
		MatrCopy_4x4(camera.matrix,l_res);
    }
    if (p_angle_z)
    {
        MatrIdentity_4x4(l_matrix);
        l_matrix[0][0]=(matr_cos_table[p_angle_z]);
        l_matrix[0][1]=(matr_sin_table[p_angle_z]);
        l_matrix[1][0]=(-matr_sin_table[p_angle_z]);
        l_matrix[1][1]=(matr_cos_table[p_angle_z]);
		MatrMul_4x4_4x4(camera.matrix,l_matrix,l_res);
		MatrCopy_4x4(camera.matrix,l_res);
    }
}
