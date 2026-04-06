#include <stdio.h>
#include <pthread.h>


void* afficher_tableau(void* arg) 
{
    int* tab = (int*)arg;
    
    printf("Contenu du tableau dans le thread : ");
    for (int i = 0; i < 5; i++) 
    {
        printf("%d ", tab[i]);
    }
    printf("\n");
    
    return NULL;
}

int main() 
{
    pthread_t thread;
    int mon_tableau[] = {10, 20, 30, 40, 50};

   
    pthread_create(&thread, NULL, afficher_tableau, (void*)mon_tableau);

    pthread_join(thread, NULL);

    return 0;
}