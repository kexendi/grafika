#include <stdio.h>
#include <windows.h>
#include "glut.h"
#include "load_bmp.h"

int num_texture=-1; //számláló hogy tudjuk melyik az utolsó textúra

int LoadBMP(char *p_filename) 
{
    int i, j=0; 
    FILE *l_file; //Fájlból való beolvasás
    unsigned char *l_texture; //memória pointer, ami tartalmazza a textúrát
     
    BITMAPFILEHEADER fileheader; 
    BITMAPINFOHEADER infoheader;
    RGBTRIPLE rgb;

    num_texture++; // kövi textúra

 	if (p_filename=='\0') return(-1);

	if((l_file = fopen(p_filename, "rb"))==NULL) 
	{
        MessageBox(NULL,"Nincs textúra","Hiba",MB_OK | MB_ICONERROR);
		return (-1);
	}
    // Olvasás File-ból
    fread(&fileheader, sizeof(fileheader), 1, l_file); 
    fseek(l_file, sizeof(fileheader), SEEK_SET); 
    fread(&infoheader, sizeof(infoheader), 1, l_file); 

    // Beszúrás a memóriába
    l_texture = (byte *) malloc(infoheader.biWidth * infoheader.biHeight * 4);
    memset(l_texture, 0, infoheader.biWidth * infoheader.biHeight * 4);
 
    // Textúra kiolvasása pointerenként
    for (i=0; i < infoheader.biWidth*infoheader.biHeight; i++)
    {            
            // szín
            fread(&rgb, sizeof(rgb), 1, l_file); 

            // tárolása
            l_texture[j+0] = rgb.rgbtRed; // piros
            l_texture[j+1] = rgb.rgbtGreen; // zöld
            l_texture[j+2] = rgb.rgbtBlue; // kék
            l_texture[j+3] = (rgb.rgbtRed+rgb.rgbtGreen+rgb.rgbtBlue)/3; // alfa (opacity)
            j += 4; 
    }

    fclose(l_file);
     
    glBindTexture(GL_TEXTURE_2D, num_texture);

    // Textúra beállítása, ráillesztése
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST); 
    glTexImage2D(GL_TEXTURE_2D, 0, 4, infoheader.biWidth, infoheader.biHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 4, infoheader.biWidth, infoheader.biHeight, GL_RGBA, GL_UNSIGNED_BYTE, l_texture);

    free(l_texture);

    return (num_texture);
}