#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


pthread_barrier_t barriere; 

void* travail_thread(void* arg) 
{

    int id = *((int*)arg);
    sleep((rand() % 5) + 1);
    printf("Thread %d arrivé au rendez-vous.\n", id);
    
    // Bloque ici jusqu'à ce que N threads aient appelé cette fonction
    pthread_barrier_wait(&barriere);
    
    printf("Thread %d franchit la barrière !\n", id);
    return NULL;
}

int main(int argc, char *argv[]) 
{
    if (argc < 2) 
    {
        return 1;
    }
    int n = atoi(argv[1]);
    pthread_t threads[n];
    int ids[n];

    pthread_barrier_init(&barriere, NULL, n);

    for (int i = 0; i < n; i++) 
    {
        ids[i] = i;
        pthread_create(&threads[i], NULL, travail_thread, &ids[i]);
    }

    for (int i = 0; i < n; i++) 
    {
        pthread_join(threads[i], NULL);
    }
    pthread_barrier_destroy(&barriere);
    return 0;
}