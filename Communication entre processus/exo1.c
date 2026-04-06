#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() 
{
    int p[2];
    pipe(p);

    if (fork() == 0) 
    {
        
        char mot[50];
        int resultat;
        printf("Saisir un mot : ");
        scanf("%s", mot);

        write(p[1], mot, 50);     
        read(p[0], &resultat, sizeof(int)); 
        
        printf("Résultat : %d\n", resultat);
        exit(0);
    } 
    else 
    {
        
        char mot_cherche[50], mot_fichier[50];
        int trouve = 0;
        FILE *f = fopen("texte.txt", "r");

        read(p[0], mot_cherche, 50); 

        if (f) 
        {
            while (fscanf(f, "%s", mot_fichier) != EOF) 
            {
                if (strcmp(mot_cherche, mot_fichier) == 0) 
                {
                    trouve = 1;
                    break;
                }
            }
            fclose(f);
        }

        write(p[1], &trouve, sizeof(int)); 
    }
    return 0;
}