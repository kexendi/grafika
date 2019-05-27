#ifdef __WIN32__
#include <windows.h>
#endif

#include "glut.h"
#include "load_bmp.h"
#include "fonts.h"
#include "main.h"
#include <string.h>

int fonts_qty=0; // max betűtípus amit kezel
font_type font[MAX_FONTS]; // betűtípusok száma


char FontCreate(char *p_file_name,int p_grid_x_qty,int p_grid_y_qty,int p_fonts_start_pos,int p_fonts_end_pos,int p_ascii_offset,int p_fonts_spacing)
{
	int i; 
	int l_x,l_y; 	
	float l_x_inc,l_y_inc; 
	int l_image_width,l_image_height;
	float l_font_width, l_font_height;

    font[fonts_qty].list_base=glGenLists(p_fonts_end_pos-p_fonts_start_pos); 
    font[fonts_qty].texture_id=LoadBMP(p_file_name); 	
    if (font[fonts_qty].texture_id == -1) return (0); 
	glBindTexture(GL_TEXTURE_2D, font[fonts_qty].texture_id); 
	glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_WIDTH,&l_image_width);
	glGetTexLevelParameteriv(GL_TEXTURE_2D,0,GL_TEXTURE_HEIGHT,&l_image_height); 
	l_font_width=l_image_width/p_grid_x_qty; 
	l_font_height=l_image_height/p_grid_y_qty; 

	l_x=p_fonts_start_pos%p_grid_x_qty; 
	l_y=p_fonts_start_pos/p_grid_y_qty; 
	l_x_inc=1.0f/p_grid_x_qty;
	l_y_inc=1.0f/p_grid_y_qty; 

	for (i=p_fonts_start_pos;i<=p_fonts_end_pos;i++)
	{			
		glNewList(font[fonts_qty].list_base+i+p_ascii_offset,GL_COMPILE);

		glBegin(GL_QUADS);

		glTexCoord2f(l_x*l_x_inc,1-l_y*l_y_inc-l_y_inc);
		glVertex2i(0,0);

		glTexCoord2f(l_x*l_x_inc+l_x_inc,1-l_y*l_y_inc-l_y_inc);
		glVertex2i(l_font_width,0);

		glTexCoord2f(l_x*l_x_inc+l_x_inc,1-l_y*l_y_inc);
		glVertex2i(l_font_width,l_font_height);

		glTexCoord2f(l_x*l_x_inc,1-l_y*l_y_inc);
		glVertex2i(0,l_font_height);

		glEnd();

		glTranslated(p_fonts_spacing,0,0);// távolság a karakterek között
		glEndList();

		l_x++;
		if (l_x>=p_grid_x_qty) {l_x=0;l_y++;}
	}                                                                                                 
	fonts_qty++; 
	return (1); 
}


void FontPrint(int p_font, int p_x, int p_y, char *p_string)
{
	glBindTexture(GL_TEXTURE_2D, font[p_font].texture_id); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); 
	glEnable(GL_BLEND);
    glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION); 
	glPushMatrix(); 
    glLoadIdentity();
    glOrtho(0,screen_width,0,screen_height,-1,1);
        
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix(); 
    glLoadIdentity(); 
    glTranslated(p_x,p_y,0); // hova írja
    glListBase(font[p_font].list_base); //hol a betű
	glCallLists(strlen(p_string),GL_BYTE,p_string); // kiírás
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix(); 
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_BLEND); 
    glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
}
