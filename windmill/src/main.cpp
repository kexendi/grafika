#ifdef __WIN32__
#include <windows.h>
#endif

#include "stdio.h"
#include "glut.h"
#include "load_bmp.h"
#include "load_3ds.h"
#include "object.h"
#include "camera.h"
#include "fonts.h"

int screen_width=1280;
int screen_height=960;


bool help = false;
bool cam = false;
bool speed = false;
int szogseb = 5;

int filling=1; 

GLfloat light_ambient[]= { 0.5f, 0.5f, 0.5f, 0.5f };
GLfloat light_diffuse[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat light_specular[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat light_position[]= { 100.0f, 0.0f, -10.0f, 1.0f };

GLfloat mat_ambient[]= { 0.2f, 0.2f, 0.2f, 0.0f };
GLfloat mat_diffuse[]= { 1.0f, 1.0f, 1.0f, 0.0f };
GLfloat mat_specular[]= { 0.2f, 0.2f, 0.2f, 0.0f };
GLfloat mat_shininess[]= { 100.0f };



void init(void)
{
	MatrGenerateLookupTab();

    glClearColor(0.0, 0.0, 0.0, 0.0); 

    glViewport(0,0,screen_width,screen_height);  

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); 
    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,5.0f,10000.0f);
   
    glLightfv (GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv (GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv (GL_LIGHT1, GL_POSITION, light_position);    
    glEnable (GL_LIGHT1);
    glEnable (GL_LIGHTING);

	glMaterialfv (GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv (GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv (GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv (GL_FRONT, GL_SHININESS, mat_shininess);    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 

    glShadeModel(GL_SMOOTH); 
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); 
    glEnable(GL_TEXTURE_2D); 
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL); 
	glEnable(GL_CULL_FACE); 
    glEnable(GL_DEPTH_TEST); 
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	FontCreate("../textures/font0.bmp",16,16,0,256,0,14);

	MatrIdentity_4x4(camera.matrix);
	camera.type=0;
	camera.n_object=0;
	
	ObjLoad ("../3ds/allvany.3ds","		../textures/allvany.bmp",			0.0, 0.0, -100.0,    	-900,0,0);
	ObjLoad ("../3ds/tengely.3ds","		../textures/tengely.bmp",		    0.0, 0.0, -100.0,    	-900,0,0);
	ObjLoad ("../3ds/lapat.3ds","		../textures/lapat.bmp",				0.0, 0.0, -100.0,    	-900,0,0);
	ObjLoad ("../3ds/land.3ds","		../textures/grass.bmp",				0.0, 11.0, 0.  0,    	-900,0,0);
	ObjLoad ("../3ds/skybox.3ds","		../textures/sky.bmp",				0.0, 11.0, 0.  0,    	-900,0,0);
}




void resize (int p_width, int p_height)
{
	if (screen_width==0 && screen_height==0) 
		exit(0);

    screen_width=p_width; 
    screen_height=p_height; 

    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glViewport(0,0,screen_width,screen_height); 

    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    gluPerspective(45.0f,(GLfloat)screen_width/(GLfloat)screen_height,5.0f,10000.0f);

    glutPostRedisplay (); 
}



void keyboard(unsigned char p_key, int p_x, int p_y)
{  
    switch (p_key)
    {

		case '+':
			for (int i = 0; i < 4; i++){
			light_ambient[i] = light_ambient[i] + 0.1;
			light_diffuse[i] = light_diffuse[i] + 0.1;
			light_specular[i] =light_specular[i] + 0.1;
			 glLightfv (GL_LIGHT1, GL_AMBIENT, light_ambient);
			 glLightfv (GL_LIGHT1, GL_DIFFUSE, light_diffuse);
			 glLightfv (GL_LIGHT1, GL_SPECULAR, light_specular);
			}
			break;

		case '-':
			for (int i = 0; i < 4; i++){
			light_ambient[i] = light_ambient[i] - 0.1;
			light_diffuse[i] = light_diffuse[i] - 0.1;
			light_specular[i] =light_specular[i] - 0.1;
			 glLightfv (GL_LIGHT1, GL_AMBIENT, light_ambient);
			 glLightfv (GL_LIGHT1, GL_DIFFUSE, light_diffuse);
			 glLightfv (GL_LIGHT1, GL_SPECULAR, light_specular);
			}
			break;			

		case 27:
			exit(0);
		break;
    }
}




void keyboard_s (int p_key, int p_x, int py)
{
    switch (p_key)
    {
        case GLUT_KEY_UP:
			CamTranslate(0,0,5);
        break;
        case GLUT_KEY_DOWN:
			CamTranslate(0,0,-5);
        break;
	

        case GLUT_KEY_LEFT:	
			CamTranslate(8,0,0);
			CamRotate(0,10,0);
        break;
        case GLUT_KEY_RIGHT:
			CamTranslate(-8,0,0);
			CamRotate(0,-10,0);
        break;

		case GLUT_KEY_F1:
			if(help == false){
				help = true;
			}else{
			help = false;
			}
		break;
		case GLUT_KEY_F2:
			if(szogseb < 30)
			szogseb++;
       break;
	   	case GLUT_KEY_F3:
			if(szogseb > 5)
			szogseb--;
       break;
    }
}



void display(void)
{
    int i;
	int l_n_font=0;
	char l_string[100];
	GLfloat l_feed_buffer[10];

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); 
    glLoadIdentity();
	
	switch (camera.type)
	{
		case 0:
			glLoadMatrixf(&camera.matrix[0][0]); 
		break;
	}

	glLightfv (GL_LIGHT1, GL_POSITION, light_position); 

    for (i=0;i<obj_qty;i++)
	{
		glPushMatrix(); 
	
		glMultMatrixf(&object[i].matrix[0][0]); 
		
		if (object[i].id_texture!=-1) 
		{
			glBindTexture(GL_TEXTURE_2D, object[i].id_texture);
		    glEnable(GL_TEXTURE_2D); 
		}
		else
		    glDisable(GL_TEXTURE_2D); 

        glVertexPointer(3,GL_FLOAT,3*sizeof(float),&object[i].vertex[0].x);
	    glNormalPointer(GL_FLOAT,3*sizeof(float),&object[i].normal[0].x);
		glTexCoordPointer(2,GL_FLOAT,2*sizeof(float),&object[i].mapcoord[0].u);
	    glDrawElements(GL_TRIANGLES,object[i].polygons_qty*3, GL_UNSIGNED_SHORT, &object[i].polygon[0].a);

		glPopMatrix(); 
	}

    for (i=0;i<obj_qty;i++)
	{
		glPushMatrix(); 
	
		glMultMatrixf(&object[i].matrix[0][0]); 
		glEnable(GL_TEXTURE_2D); 

		l_feed_buffer[0]=-1; l_feed_buffer[1]=-1; l_feed_buffer[2]=-1;
		glFeedbackBuffer(3,GL_3D,l_feed_buffer);
		glRenderMode(GL_FEEDBACK); 
		glBegin(GL_POINTS); 
			glVertex3f(0.0f,0.0f,0.0f); 
		glEnd();
		glRenderMode(GL_RENDER); 
		if (l_feed_buffer[0]>=0 && l_feed_buffer[1]>=0 && l_feed_buffer[2]>=0)
		{
			if (i==obj_control) 
			    glColor4f(1.0f,0.0f,0.0f,1.0f); 
			else 
			    glColor4f(1.0f,1.0f,1.0f,1.0f);			
		}
		glPopMatrix(); 
	}

    glColor4f(0.0f,0.0f,0.0f,1.0f);
	
	if(help == false){
	sprintf(l_string,"Help: F1");
	FontPrint(0,0,screen_height-20,l_string);
	}


	if(help == true){
	sprintf(l_string,"Menu");
	FontPrint(0,0,screen_height-20,l_string);
	sprintf(l_string,"Kamera:");
	FontPrint(0,0,screen_height-40,l_string);
	sprintf(l_string,"\t Elore: Nyil fel");
	FontPrint(0,0,screen_height-60,l_string);
	sprintf(l_string,"\t Hatra: Nyil le");
	FontPrint(0,0,screen_height-80,l_string);
	sprintf(l_string,"\t Jobbra: Nyil jobb");
	FontPrint(0,0,screen_height-100,l_string);
	sprintf(l_string,"\t Balra: Nyil bal");
	FontPrint(0,0,screen_height-120,l_string);
	sprintf(l_string,"Feny: +, -");
	FontPrint(0,0,screen_height-140,l_string);
	sprintf(l_string,"Sebesseg:");
	FontPrint(0,0,screen_height-160,l_string);
	sprintf(l_string,"\t Gyorsitas: F2");
	FontPrint(0,0,screen_height-180,l_string);
	sprintf(l_string,"\t Lassitas: F3");
	FontPrint(0,0,screen_height-200,l_string);

	}

	glFlush(); 
    glutSwapBuffers(); 
	
	ObjRotate(&object[2],0,szogseb,0);
	if(cam == false){
	CamTranslate(0,0,-450);
	cam = true;
	}
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(screen_width,screen_height);
    glutInitWindowPosition(0,0);
    glutCreateWindow("WindMill");    
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutReshapeFunc (resize);
    glutKeyboardFunc (keyboard);
    glutSpecialFunc (keyboard_s);
    init();
    glutMainLoop();

    return(0);    
}
