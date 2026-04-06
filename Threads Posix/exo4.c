#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct Tableau
{ 
    int *tab; 
    int n; 
} Tableau;
typedef struct Paquet
{ 
    Tableau *T1; 
    Tableau *T2; 
} Paquet;


void* generer(void* arg) 
{
    Tableau *t = (Tableau*)arg;
    t->tab = malloc(t->n * sizeof(int));
    for (int i = 0; i < t->n; i++) 
    {
        t->tab[i] = rand() % 100;
    }
    return NULL;
}


void* verifier_inclusion(void* arg) 
{
    Paquet *p = (Paquet*)arg;
    int inclus = 1;
    for (int i = 0; i < p->T1->n; i++) 
    {
        int trouve = 0;
        for (int j = 0; j < p->T2->n; j++) 
        {
            if (p->T1->tab[i] == p->T2->tab[j]) 
            { 
                trouve = 1; 
                break; 
            }
        }
        if (!trouve) 
        {
            inclus = 0; 
            break; 
        }
    }
    printf("\nRésultat : T1 est %s dans T2\n", inclus ? "inclus" : "NON inclus");
    return NULL;
}


void* guetter_annulation(void* arg) 
{
    if (getchar() == 'A') 
    {
        printf("\nProgramme annulé par l'utilisateur.\n");
        exit(0);
    }
    return NULL;
}

int main() 
{
    srand(time(NULL));
    pthread_t th1, th2, th3, th_abort;
    Tableau t1 = {NULL, 5}, t2 = {NULL, 10};
    Paquet p = {&t1, &t2};

    
    pthread_create(&th_abort, NULL, guetter_annulation, NULL);
    pthread_detach(th_abort); 

    pthread_create(&th1, NULL, generer, &t1);
    pthread_create(&th2, NULL, generer, &t2);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    
    pthread_create(&th3, NULL, verifier_inclusion, &p);
    pthread_join(th3, NULL);

    free(t1.tab); free(t2.tab);
    return 0;
}