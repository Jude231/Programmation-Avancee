#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

unsigned char base[15] = {0};
int nb_lecteurs = 0;

sem_t sem_base;
pthread_mutex_t mutex_lecteurs = PTHREAD_MUTEX_INITIALIZER;

void* lecteur(void* arg) 
{
    int id = *((int*)arg);
    while (1) 
    {
        sleep((rand() % 3) + 1);

        // Arrivée d'un lecteur
        pthread_mutex_lock(&mutex_lecteurs);
        nb_lecteurs++;
        if (nb_lecteurs == 1) 
        {
            sem_wait(&sem_base); // Le 1er bloque les écrivains
        }
        pthread_mutex_unlock(&mutex_lecteurs);

        // Section Critique : Lecture
        int pos = rand() % 15;
        printf("[Lecteur %d] Lit base[%d] = %d (Lecteurs actifs: %d)\n", id, pos, base[pos], nb_lecteurs);

        // Départ d'un lecteur
        pthread_mutex_lock(&mutex_lecteurs);
        nb_lecteurs--;
        if (nb_lecteurs == 0) 
        {
            sem_post(&sem_base); // Le dernier libère les écrivains
        }
        pthread_mutex_unlock(&mutex_lecteurs);
    }
}

void* ecrivain(void* arg) 
{
    int id = *((int*)arg);
    while (1) 
    {
        sleep((rand() % 10) + 1);

        sem_wait(&sem_base); // Un écrivain a besoin d'un accès exclusif
        
        // Section Critique : Écriture
        int pos = rand() % 15;
        base[pos] = rand() % 256;
        printf("[Écrivain %d] !!! MODIFIE base[%d] = %d !!!\n", id, pos, base[pos]);
        
        sem_post(&sem_base);
    }
}

int main() 
{
    int n, m;
    printf("Nombre de lecteurs (N) et écrivains (M) : ");
    scanf("%d %d", &n, &m);

    sem_init(&sem_base, 0, 1);
    pthread_t th_l[n], th_e[m];
    int id_l[n], id_e[m];

    for (int i = 0; i < n; i++) 
    { 
        id_l[i] = i; pthread_create(&th_l[i], NULL, lecteur, &id_l[i]); 
    }
    for (int i = 0; i < m; i++) 
    { 
        id_e[i] = i; pthread_create(&th_e[i], NULL, ecrivain, &id_e[i]); 
    }

    for (int i = 0; i < n; i++) 
    {
        pthread_join(th_l[i], NULL);
    }
    for (int i = 0; i < m; i++) 
    {
        pthread_join(th_e[i], NULL);
    }
    return 0;
}