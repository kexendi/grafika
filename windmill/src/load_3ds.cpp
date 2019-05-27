#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <io.h>
#include "object.h"
#include "load_3ds.h"


char Load3DS(obj_type_ptr p_object, char *p_filename)
{
	int i; 
	
	FILE *l_file; 
	
	unsigned short l_chunk_id; //chunk aznosító
	unsigned int l_chunk_lenght; //chunk hossz

	unsigned char l_char;
	unsigned short l_qty; //elemek száma / chunk

	unsigned short l_face_flags;

	if (p_filename=='\0') return(0);

	if ((l_file=fopen (p_filename, "rb"))== NULL) 
	{
        MessageBox(NULL,"Nincs meg a modell","Hiba",MB_OK | MB_ICONERROR);
		return (0);
	}

	while (ftell (l_file) < filelength (fileno (l_file))) //Loop to scan the whole file 
	{
		//getche(); //Insert this command for debug (to wait for keypress for each chuck reading)

		fread (&l_chunk_id, 2, 1, l_file); //Read the chunk header
		printf("ChunkID: %x\n",l_chunk_id); 
		fread (&l_chunk_lenght, 4, 1, l_file); //Read the lenght of the chunk
		printf("ChunkLenght: %x\n",l_chunk_lenght);

		switch (l_chunk_id)
        {
			case 0x4d4d: 
			break;    
			case 0x3d3d:
			break;
			
			case 0x4000: 
				i=0;
				do
				{
					fread (&l_char, 1, 1, l_file);
                    p_object->name[i]=l_char;
					i++;
                }while(l_char != '\0' && i<20);
			break;
			case 0x4100:
			break;
			
			case 0x4110: 
				fread (&l_qty, sizeof (unsigned short), 1, l_file);
                p_object->vertices_qty = l_qty;
                printf("Vertikálisok száma: %d\n",l_qty);
				if (l_qty>MAX_VERTICES) 
				{
			        MessageBox(NULL,"Túl sok vertikális","Hiba",MB_OK | MB_ICONERROR);
					return (0);
				}
                for (i=0; i<l_qty; i++)
                {
					fread (&p_object->vertex[i].x, sizeof(float), 1, l_file);
 					printf("Vertikális lista x: %f\n",p_object->vertex[i].x);
                    fread (&p_object->vertex[i].y, sizeof(float), 1, l_file);
 					printf("Vertikális lista y: %f\n",p_object->vertex[i].y);
					fread (&p_object->vertex[i].z, sizeof(float), 1, l_file);
 					printf("Vertikális lista z: %f\n",p_object->vertex[i].z);
				}
				break;

			case 0x4120:
				fread (&l_qty, sizeof (unsigned short), 1, l_file);
                p_object->polygons_qty = l_qty;
                printf("Poligon szám: %d\n",l_qty); 
				if (l_qty>MAX_POLYGONS) 
				{
			        MessageBox(NULL,"Túl sok poligon","Hiba",MB_OK | MB_ICONERROR);
					return (0);
				}				
                for (i=0; i<l_qty; i++)
                {
					fread (&p_object->polygon[i].a, sizeof (unsigned short), 1, l_file);
					printf("Poligon pont a: %d\n",p_object->polygon[i].a);
					fread (&p_object->polygon[i].b, sizeof (unsigned short), 1, l_file);
					printf("Poligon pont b: %d\n",p_object->polygon[i].b);
					fread (&p_object->polygon[i].c, sizeof (unsigned short), 1, l_file);
					printf("Poligon pont c: %d\n",p_object->polygon[i].c);
					fread (&l_face_flags, sizeof (unsigned short), 1, l_file);
					printf("Face flags: %x\n",l_face_flags);
				}
                break;

			case 0x4140:
				fread (&l_qty, sizeof (unsigned short), 1, l_file);
				for (i=0; i<l_qty; i++)
				{
					fread (&p_object->mapcoord[i].u, sizeof (float), 1, l_file);
					printf("Mapping lista u: %f\n",p_object->mapcoord[i].u);
                    fread (&p_object->mapcoord[i].v, sizeof (float), 1, l_file);
					printf("Mapping lista v: %f\n",p_object->mapcoord[i].v);
				}
                break;
			case 0xAFFF:
			break;

			case 0xA020: 
			break;
			default:
				 fseek(l_file, l_chunk_lenght-6, SEEK_CUR);
        } 
	}
	fclose (l_file); 
	return (1); 
}
