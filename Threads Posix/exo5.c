#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int compt = 0;
int limite;
pthread_mutex_t verrou = PTHREAD_MUTEX_INITIALIZER;

// Thread 1 : Incrémentateur
void* incrementer(void* arg) 
{
    while (1) 
    {
        pthread_mutex_lock(&verrou);
        if (compt >= limite) 
        {
            pthread_mutex_unlock(&verrou);
            break;
        }
        compt++;
        printf("[Thread 1] Compteur incrémenté : %d\n", compt);
        pthread_mutex_unlock(&verrou);

        sleep((rand() % 5) + 1);
    }
    return NULL;
}

// Thread 2 : Afficheur périodique
void* afficher(void* arg) 
{
    while (1) 
    {
        sleep(2);
        
        pthread_mutex_lock(&verrou);
        printf("[Thread 2] Valeur actuelle : %d\n", compt);
        if (compt >= limite) 
        {
            pthread_mutex_unlock(&verrou);
            break;
        }
        pthread_mutex_unlock(&verrou);
    }
    return NULL;
}

int main(int argc, char *argv[]) 
{
    if (argc < 2) 
    {
        return 1;
    }
    limite = atoi(argv[1]);
    srand(time(NULL));

    pthread_t t1, t2;

    pthread_create(&t1, NULL, incrementer, NULL);
    pthread_create(&t2, NULL, afficher, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Fin du programme. Valeur finale : %d\n", compt);
    pthread_mutex_destroy(&verrou);
    
    return 0;
}