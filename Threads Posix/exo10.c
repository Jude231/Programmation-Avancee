#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define TAILLE 10
unsigned char pile[TAILLE];
int top = 0; // Indice pour la gestion LIFO (Last-In, First-Out)

sem_t sem_libres, sem_prets;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* producteur(void* arg) 
{
    int id = *((int*)arg);
    while (1) 
    {
        unsigned char objet = rand() % 256;
        sleep((rand() % 3) + 1);

        sem_wait(&sem_libres); // Attend une place libre
        pthread_mutex_lock(&mutex);
        
        pile[top++] = objet; // Empile (LIFO)
        printf("[Prod %d] + Déposé: %02X (Stock: %d/%d)\n", id, objet, top, TAILLE);
        
        pthread_mutex_unlock(&mutex);
        sem_post(&sem_prets); // Signale un objet prêt
    }
}

void* consommateur(void* arg) 
{
    int id = *((int*)arg);
    while (1) 
    {
        sleep((rand() % 3) + 1);

        sem_wait(&sem_prets); // Attend un objet
        pthread_mutex_lock(&mutex);
        
        unsigned char objet = pile[--top]; // Dépile (LIFO)
        printf("[Cons %d] - Retiré: %02X (Stock: %d/%d)\n", id, objet, top, TAILLE);
        
        pthread_mutex_unlock(&mutex);
        sem_post(&sem_libres); // Signale une place libérée
    }
}

int main() 
{
    int n, m;
    printf("Nombre de producteurs (N) et consommateurs (M) : ");
    scanf("%d %d", &n, &m);

    sem_init(&sem_libres, 0, TAILLE);
    sem_init(&sem_prets, 0, 0);

    pthread_t prods[n], cons[m];
    int id_p[n], id_c[m];

    for (int i = 0; i < n; i++) 
    { 
        id_p[i] = i; pthread_create(&prods[i], NULL, producteur, &id_p[i]); 
    }
    for (int i = 0; i < m; i++) 
    { 
        id_c[i] = i; pthread_create(&cons[i], NULL, consommateur, &id_c[i]); 
    }

    for (int i = 0; i < n; i++) 
    { 
        pthread_join(prods[i], NULL); 
    }
    for (int i = 0; i < m; i++) 
    {
        pthread_join(cons[i], NULL);
    }

    return 0;
}