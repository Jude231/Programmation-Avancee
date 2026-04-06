#include <stdio.h>

int main() 
{
    long total = 78000000;
    int bytes_per_sect = 1024, sect_per_face = 60, faces = 4;

    int pos_in_sect = total % bytes_per_sect;
    long total_sect = total / bytes_per_sect;
    
    int sect_idx = total_sect % sect_per_face;
    int face_idx = (total_sect / sect_per_face) % faces;
    int cyl_idx = (total_sect / sect_per_face) / faces;

    printf("Cyl:%d, Face:%d, Sect:%d, Pos:%d\n", cyl_idx, face_idx, sect_idx, pos_in_sect);
    return 0;
}