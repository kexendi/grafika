#ifndef _OBJECT_H
#define _OBJECT_H

#include "mat_vect.h"
#include "mat_matr.h"

#define MAX_VERTICES 10000 // max vertikálisok
#define MAX_POLYGONS 10000 // max poligonszám
#define MAX_OBJECTS 100 // max objektum ami betölthető

typedef struct{
    float x,y,z;
}vertex_type;

typedef struct{
    unsigned short a,b,c;
}polygon_type;

typedef struct{
    float u,v;
}mapcoord_type;

typedef struct{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
}rgba_type;

typedef struct {

	rgba_type mat_ambient;
	rgba_type mat_diffuse;
	rgba_type mat_specular;
	unsigned short mat_shininess;

} material_type;

typedef struct {

	char name[20]; // objektum neve
    
	int vertices_qty; // vertikálisainak a száma
    int polygons_qty; // poligonok száma

    vertex_type vertex[MAX_VERTICES]; // ezeket tömbbe redezi
    vertex_type normal[MAX_VERTICES]; 
    polygon_type polygon[MAX_POLYGONS]; 
    mapcoord_type mapcoord[MAX_VERTICES]; 

    int id_texture; // textúrák száma

	matrix_4x4_type matrix; // objektum mátrix

	material_type material[10];


} obj_type, *obj_type_ptr;

extern obj_type object[MAX_OBJECTS];
extern int obj_qty;
extern int obj_control;

extern char ObjLoad(char *p_object_name, char *p_texture_name, float p_pos_x, float p_pos_y, float p_pos_z, int p_rot_x, int p_rot_y, int p_rot_z);
extern void ObjCalcNormals(obj_type_ptr p_object);
extern void ObjPosition (obj_type_ptr p_object,float p_x,float p_y,float p_z);
extern void ObjTranslate (obj_type_ptr p_object,float p_x,float p_y,float p_z);
extern void ObjTranslateW (obj_type_ptr p_object,float p_x,float p_y,float p_z);
extern void ObjRotate (obj_type_ptr p_object,int p_angle_x,int p_angle_y,int p_angle_z);

#endif