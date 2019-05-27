#include <math.h>
#include "mat_vect.h"

void VectCreate (p3d_ptr_type p_start, p3d_ptr_type p_end, p3d_ptr_type p_vector)
{
    p_vector->x = p_end->x - p_start->x;
    p_vector->y = p_end->y - p_start->y;
    p_vector->z = p_end->z - p_start->z;
    VectNormalize(p_vector);
}

float VectLenght (p3d_ptr_type p_vector)
{
	return (float)(sqrt(p_vector->x*p_vector->x + p_vector->y*p_vector->y + p_vector->z*p_vector->z));
}


void VectNormalize(p3d_ptr_type p_vector)
{
  float l_lenght;
  
  l_lenght = VectLenght(p_vector);
  if (l_lenght==0) l_lenght=1;
  p_vector->x /= l_lenght;
  p_vector->y /= l_lenght;
  p_vector->z /= l_lenght;
}


float VectScalarProduct (p3d_ptr_type p_vector1,p3d_ptr_type p_vector2)
{
    return (p_vector1->x*p_vector2->x + p_vector1->y*p_vector2->y + p_vector1->z*p_vector2->z);
}


void VectDotProduct (p3d_ptr_type p_vector1,p3d_ptr_type p_vector2,p3d_ptr_type p_normal)
{
    p_normal->x=(p_vector1->y * p_vector2->z) - (p_vector1->z * p_vector2->y);
    p_normal->y=(p_vector1->z * p_vector2->x) - (p_vector1->x * p_vector2->z);
    p_normal->z=(p_vector1->x * p_vector2->y) - (p_vector1->y * p_vector2->x);
}


