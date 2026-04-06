#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>


double u = 1.0;
int compteur = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Fonction f1(x) = 1/4 * (x - 1)^2
double f1(double x) 
{
    return (1.0/4.0) * pow(x - 1.0, 2);
}

// Fonction f2(x) = 1/6 * (x - 2)^2
double f2(double x) 
{
    return (1.0/6.0) * pow(x - 2.0, 2);
}

void* thread_fonction(void* arg) 
{
    int id = *((int*)arg);
    
    while (1) 
    {
        pthread_mutex_lock(&mutex);
        
        
        compteur++;
        if (id == 1) 
        {
            u = f1(u);
        }   
        else 
        {
            u = f2(u);
        }
        
        printf("[Thread %d] Itération %d : u = %f\n", id, compteur, u);
        
        pthread_mutex_unlock(&mutex);

        sleep((rand() % 5) + 1);
    }
    return NULL;
}

int main() 
{
    srand(time(NULL));
    pthread_t t1, t2;
    int id1 = 1, id2 = 2;

    
    pthread_create(&t1, NULL, thread_fonction, &id1);
    pthread_create(&t2, NULL, thread_fonction, &id2);

    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
