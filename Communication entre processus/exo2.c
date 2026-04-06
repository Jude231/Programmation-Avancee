#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() 
{
    int p1[2], p2[2]; // Deux tubes 
    pipe(p1); pipe(p2);

    if (fork() == 0) 
    {
        
        char mot[50];
        int res;
        printf("Saisir un mot : ");
        scanf("%s", mot);

        write(p1[1], mot, 50);    // Envoie au père
        read(p2[0], &res, sizeof(int)); // Reçoit du père
        printf("Résultat : %d\n", res);
        exit(0);
    } 
    else 
    {
      
        dup2(p1[0], STDIN_FILENO);
        dup2(p2[1], STDOUT_FILENO);

        char mot_cherche[50], f_mot[50];
        int trouve = 0;
        
     
        scanf("%s", mot_cherche);

        FILE *f = fopen("texte.txt", "r");
        if (f) 
        {
            while (fscanf(f, "%s", f_mot) != EOF) 
            {
                if (strcmp(mot_cherche, f_mot) == 0) { trouve = 1; break; }
            }
            fclose(f);
        }

        dprintf(STDOUT_FILENO, "%d", trouve);
    }
    return 0;
}