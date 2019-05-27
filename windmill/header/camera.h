#include "mat_matr.h"

typedef struct {

	int type;//0=szabad mozgás 1=Visszafele 2=belefele
	int n_object; // objektumok száma, amihez kapcsolódik (amit néz)
	matrix_4x4_type matrix;

} camera_type, *camera_type_ptr;

extern camera_type camera;

extern void CamTranslate (float p_x,float p_y,float p_z);
extern void CamTranslateW (float p_x,float p_y,float p_z);
extern void CamRotate (int p_angle_x,int p_angle_y,int p_angle_z);
