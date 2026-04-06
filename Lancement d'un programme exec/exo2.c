#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
{
    if (argc != 2) return 1; 

    char commande[256];
    
    sprintf(commande, "cp -r . %s", argv[1]);

    return system(commande);
}