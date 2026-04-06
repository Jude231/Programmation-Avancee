#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() 
{
    char dest[256], cmd[512];

    while (1) 
    {
        printf("Répertoire destination (ou 'quitter') : ");
        scanf("%s", dest);

        if (strcmp(dest, "quitter") == 0) 
        {
            break;
        }

        
        sprintf(cmd, "cp -r . %s", dest);
        system(cmd);
    }

    return 0;
}