#ifndef _LOAD_BMP_H
#define _LOAD_BMP_H

// számláló, hogy tudjuk hanyadik volt az utolsó betöltött textúra, mert az után fűzi a kövit
extern int num_texture;

extern int LoadBMP(char *p_filename);

#endif