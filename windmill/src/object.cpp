#include <math.h>
#include "load_3ds.h"
#include "load_bmp.h"
#include "object.h"

obj_type object[MAX_OBJECTS];
int objectQualty=0; //objektumok száma
int objectMoveable=0; //mozgatható objektumok száma (illetve ezt hívom meg, amikor megadom, pontosan melyik modell mozogjon)

char ObjLoad(char *p_object_name, char *p_texture_name, float p_pos_x, float p_pos_y, float p_pos_z, int p_rot_x, int p_rot_y, int p_rot_z)
{
    if (Load3DS (&object[objectQualty],p_object_name) == 0) 
        return(0); //betöltés
    
    object[objectQualty].id_texture=LoadBMP(p_texture_name); // textúra ráillesztése
	ObjCalcNormals(&object[objectQualty]); //kiszámolni a modell vertikálisainak elhelyezjedését
	MatrIdentity_4x4(object[objectQualty].matrix); //objektum mátrix inicializálása
	ObjPosition(&object[objectQualty], p_pos_x, p_pos_y, p_pos_z); // modell kezdő pozíció
	ObjRotate(&object[objectQualty], p_rot_x, p_rot_y, p_rot_z); // modell kezdő forgatás
	objectQualty++; // kövi modellre betöltésére való felkészölés (lefut megint minden)
	return (1); 
}

void ObjCalcNormals(obj_type_ptr p_object)
{
	int i;
	p3d_type l_vect1,l_vect2,l_vect3,l_vect_b1,l_vect_b2,l_normal;  //szükséges vektorok
	int l_connections_qty[MAX_VERTICES]; //poligonok száma

    // vertikálisok resetelése
	for (i=0; i<p_object->vertices_qty; i++)
	{
		p_object->normal[i].x = 0.0;
		p_object->normal[i].y = 0.0;
		p_object->normal[i].z = 0.0;
		l_connections_qty[i]=0;
	}
	
	for (i=0; i<p_object->polygons_qty; i++)
	{
        l_vect1.x = p_object->vertex[p_object->polygon[i].a].x;
        l_vect1.y = p_object->vertex[p_object->polygon[i].a].y;
        l_vect1.z = p_object->vertex[p_object->polygon[i].a].z;
        l_vect2.x = p_object->vertex[p_object->polygon[i].b].x;
        l_vect2.y = p_object->vertex[p_object->polygon[i].b].y;
        l_vect2.z = p_object->vertex[p_object->polygon[i].b].z;
        l_vect3.x = p_object->vertex[p_object->polygon[i].c].x;
        l_vect3.y = p_object->vertex[p_object->polygon[i].c].y;
        l_vect3.z = p_object->vertex[p_object->polygon[i].c].z;         
  
        // poligonszámolás
		VectCreate (&l_vect1, &l_vect2, &l_vect_b1); 
        VectCreate (&l_vect1, &l_vect3, &l_vect_b2);
        VectDotProduct (&l_vect_b1, &l_vect_b2, &l_normal); 
        VectNormalize (&l_normal); 

		l_connections_qty[p_object->polygon[i].a]+=1; 
		l_connections_qty[p_object->polygon[i].b]+=1;
		l_connections_qty[p_object->polygon[i].c]+=1;

		p_object->normal[p_object->polygon[i].a].x+=l_normal.x; 
		p_object->normal[p_object->polygon[i].a].y+=l_normal.y;
		p_object->normal[p_object->polygon[i].a].z+=l_normal.z;
		p_object->normal[p_object->polygon[i].b].x+=l_normal.x;
		p_object->normal[p_object->polygon[i].b].y+=l_normal.y;
		p_object->normal[p_object->polygon[i].b].z+=l_normal.z;
		p_object->normal[p_object->polygon[i].c].x+=l_normal.x;
		p_object->normal[p_object->polygon[i].c].y+=l_normal.y;
		p_object->normal[p_object->polygon[i].c].z+=l_normal.z;	
	}	
	
    for (i=0; i<p_object->vertices_qty; i++)
	{
		if (l_connections_qty[i]>0)
		{
			p_object->normal[i].x /= l_connections_qty[i]; 
			p_object->normal[i].y /= l_connections_qty[i];
			p_object->normal[i].z /= l_connections_qty[i];
		}
	}
}

void ObjPosition (obj_type_ptr p_object,float p_x,float p_y,float p_z)
{
	//mozgatás esetén lekéri a jelenlegi pozíciót
    p_object->matrix[3][0]=p_x;
    p_object->matrix[3][1]=p_y;
    p_object->matrix[3][2]=p_z;    
}


void ObjTranslate (obj_type_ptr p_object,float p_x,float p_y,float p_z)
{
    int j,k;
    matrix_4x4_type l_matrix, l_res;

    MatrIdentity_4x4(l_matrix);
    l_matrix[3][0]=p_x;
    l_matrix[3][1]=p_y;
    l_matrix[3][2]=p_z;

    MatrMul_4x4_4x4(l_matrix,p_object->matrix,l_res);
    for(j=0;j<4;j++)
      for(k=0;k<4;k++)
        p_object->matrix[j][k]=l_res[j][k];
}


void ObjTranslateW (obj_type_ptr p_object,float p_x,float p_y,float p_z)
{
      p_object->matrix[3][0]+=p_x;
      p_object->matrix[3][1]+=p_y;
      p_object->matrix[3][2]+=p_z;
}

/*forgatás az összes tengelyen (a tengelyt meg kell hívni, hogy tudja hol forog)*/
void ObjRotate (obj_type_ptr p_object,int p_angle_x,int p_angle_y,int p_angle_z)
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
        MatrMul_4x4_4x4(l_matrix,p_object->matrix,l_res);
        MatrCopy_4x4(p_object->matrix,l_res);
    }
    if (p_angle_y)
    {
        MatrIdentity_4x4(l_matrix);
        l_matrix[0][0]=(matr_cos_table[p_angle_y]);
        l_matrix[0][2]=(-matr_sin_table[p_angle_y]);
        l_matrix[2][0]=(matr_sin_table[p_angle_y]);
        l_matrix[2][2]=(matr_cos_table[p_angle_y]);
        MatrMul_4x4_4x4(l_matrix,p_object->matrix,l_res);
        MatrCopy_4x4(p_object->matrix,l_res);
    }
    if (p_angle_z)
    {
        MatrIdentity_4x4(l_matrix);
        l_matrix[0][0]=(matr_cos_table[p_angle_z]);
        l_matrix[0][1]=(matr_sin_table[p_angle_z]);
        l_matrix[1][0]=(-matr_sin_table[p_angle_z]);
        l_matrix[1][1]=(matr_cos_table[p_angle_z]);
        MatrMul_4x4_4x4(l_matrix,p_object->matrix,l_res);
        MatrCopy_4x4(p_object->matrix,l_res);
    }
}