#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define N 100
double tableau[N];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


void* lissage(void* arg) 
{
    while (1) 
    {
        pthread_mutex_lock(&mutex);
        for (int i = 1; i < N - 1; i++) 
        {
            tableau[i] = (tableau[i-1] + tableau[i] + tableau[i+1]) / 3.0;
        }
        pthread_mutex_unlock(&mutex);
        
        sleep((rand() % 3) + 1);
    }
    return NULL;
}

void* affichage(void* arg) 
{
    while (1) 
    {
        sleep(4);
        pthread_mutex_lock(&mutex);
        printf("\n--- État du tableau ---\n");
        for (int i = 0; i < N; i++) 
        {
            printf("%.2f ", tableau[i]);
            if ((i + 1) % 10 == 0) 
            {
                printf("\n");
            }
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t t1, t2;

    tableau[0] = 0.0;
    tableau[N-1] = 0.0;
    for (int i = 1; i < N - 1; i++) 
    {
        tableau[i] = (double)(rand() % 101);
    }

    pthread_create(&t1, NULL, lissage, NULL);
    pthread_create(&t2, NULL, affichage, NULL);

    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}