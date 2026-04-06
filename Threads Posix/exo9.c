#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

unsigned char tampon; // Variable globale (l'octet)
sem_t sem_vide;       // Autorise l'émetteur
sem_t sem_plein;      // Autorise le récepteur

void* emetteur(void* arg) 
{
    for (int i = 0; i < 10; i++) 
    {
        sleep((rand() % 3) + 1);
        unsigned char octet = (unsigned char)(rand() % 256);

        sem_wait(&sem_vide);  // Attend que le tampon soit vide
        tampon = octet;       // Dépose l'octet
        printf("[Émetteur] Octet déposé : %02X\n", octet);
        sem_post(&sem_plein); // Signale qu'un octet est prêt
    }
    return NULL;
}

void* recepteur(void* arg) 
{
    for (int i = 0; i < 10; i++) 
    {
        sleep((rand() % 3) + 1);

        sem_wait(&sem_plein); // Attend qu'un octet soit prêt
        unsigned char octet = tampon; // Lit l'octet
        printf("[Récepteur] Octet lu : %02X\n", octet);
        sem_post(&sem_vide);  // Signale que le tampon est de nouveau vide
    }
    return NULL;
}

int main() 
{
    pthread_t t1, t2;
    srand(time(NULL));

    sem_init(&sem_vide, 0, 1); 
    sem_init(&sem_plein, 0, 0); 

    pthread_create(&t1, NULL, emetteur, NULL);
    pthread_create(&t2, NULL, recepteur, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    sem_destroy(&sem_vide);
    sem_destroy(&sem_plein);
    return 0;
}