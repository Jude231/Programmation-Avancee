#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

struct TypeTableau
{
    int *tab;
    int n;
    int x;
};
typedef struct TypeTableau TypeTableau;


void* initialiser(void* arg) 
{
    TypeTableau *tt = (TypeTableau*)arg;
    tt->tab = malloc(tt->n * sizeof(int));
    srand(time(NULL));
    for (int i = 0; i < tt->n; i++) 
    {
        tt->tab[i] = rand() % 100;
        printf("%d ", tt->tab[i]); 
    }
    printf("\n");
    return NULL;
}


void* chercher(void* arg) 
{
    TypeTableau *tt = (TypeTableau*)arg;
    int *trouve = malloc(sizeof(int));
    *trouve = 0;
    for (int i = 0; i < tt->n; i++) 
    {
        if (tt->tab[i] == tt->x) 
        { 
            *trouve = 1; 
            break; 
        }
    }
    return (void*)trouve;
}

int main() {
    pthread_t t1, t2;
    TypeTableau tt;
    int *resultat;

    printf("Nombre d'éléments : ");
    scanf("%d", &tt.n);

   
    pthread_create(&t1, NULL, initialiser, &tt);

    
    printf("Entrez x à chercher : ");
    scanf("%d", &tt.x);

    
    pthread_join(t1, NULL);

    
    pthread_create(&t2, NULL, chercher, &tt);
    pthread_join(t2, (void**)&resultat);

    printf("Présent ? %d\n", *resultat);

    free(tt.tab);
    free(resultat);
    return 0;
}