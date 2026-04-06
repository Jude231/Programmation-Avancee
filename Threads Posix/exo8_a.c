#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

sem_t rendez_vous;

void* thread_T1(void* arg) 
{
    for(int i = 0; i < 10; i++) 
    {
        sleep(2); 
        printf("T1 (it %d) attend T2...\n", i+1);
        sem_wait(&rendez_vous); 
        printf("T1 repart !\n");
    }
    return NULL;
}

void* thread_T2(void* arg) 
{
    for(int i = 0; i < 10; i++) 
    {
        sleep((rand() % 6) + 4); 
        printf("T2 (it %d) arrive au rendez-vous.\n", i+1);
        sem_post(&rendez_vous); 
    }
    return NULL;
}

int main() 
{
    pthread_t t1, t2;
    sem_init(&rendez_vous, 0, 0);
    pthread_create(&t1, NULL, thread_T1, NULL);
    pthread_create(&t2, NULL, thread_T2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    sem_destroy(&rendez_vous);
    return 0;
}