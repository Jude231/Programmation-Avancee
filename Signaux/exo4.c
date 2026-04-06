#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>


sigjmp_buf point_retour;

// Gestionnaire de signal pour l'erreur de segmentation
void segfault_handler(int sig) 
{
    printf("\nErreur de segmentation détectée ! i est hors limites.\n");
    siglongjmp(point_retour, 1); 
}

int main() 
{
    int n, i, *tab;

    printf("Taille du tableau n : ");
    scanf("%d", &n);
    tab = malloc(n * sizeof(int));

    for (int j = 0; j < n; j++) 
    {
        printf("tab[%d] = ", j);
        scanf("%d", &tab[j]);
    }

    signal(SIGSEGV, segfault_handler);

 
    sigsetjmp(point_retour, 1);

    while (1) 
    {
        printf("\nQuel index i voulez-vous afficher (0 à %d) ? ", n - 1);
        if (scanf("%d", &i) != 1) 
        {
            break;
        }

       
        printf("Valeur lue : %d\n", tab[i]); 
    }

    free(tab);
    return 0;
}