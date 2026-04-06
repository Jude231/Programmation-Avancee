#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() 
{
    char f[100];

    while (1) 
    {
        printf("Fichier à ouvrir (ou 'quitter') : ");
        scanf("%s", f);

        if (strcmp(f, "quitter") == 0) 
        {
            break;
        }

        if (fork() == 0) 
        {
            
            execl("/usr/bin/emacs", "emacs", f, NULL);
            exit(0); 
        }
        
    }
    return 0;
}