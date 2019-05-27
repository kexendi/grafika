#ifndef _FONTS_H
#define _FONTS_H

#include "mat_vect.h"
#include "mat_matr.h"

#define MAX_FONTS 10 // max betűtípusok száma

typedef struct{
    
    int list_base; // opengl sajátosság
	int texture_id; //betöltéshez tartozó textúra azonosító

}font_type;

extern font_type font[MAX_FONTS];
extern char FontCreate(char *p_file_name,int p_grid_x_qty,int p_grid_y_qty,int p_fonts_start_pos,int p_fonts_end_pos,int p_ascii_offset,int p_fonts_spacing);
extern void FontPrint(int p_font, int p_x, int p_y, char *p_string);

#endif