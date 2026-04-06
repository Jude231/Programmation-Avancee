#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define TAILLE 10

void* generer_tableau(void* arg) 
{
    
    int* tab = malloc(TAILLE * sizeof(int));
    
    srand(time(NULL));
    for (int i = 0; i < TAILLE; i++) 
    {
        tab[i] = rand() % 100;
    }
    
    
    return (void*)tab;
}

int main() 
{
    pthread_t thread;
    int* resultat;

    pthread_create(&thread, NULL, generer_tableau, NULL);

   
    pthread_join(thread, (void**)&resultat);

    printf("Tableau reçu du thread : ");
    for (int i = 0; i < TAILLE; i++) 
    {
        printf("%d ", resultat[i]);
    }
    printf("\n");

    free(resultat);
    return 0;
}