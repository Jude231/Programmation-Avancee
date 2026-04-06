#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main() 
{
    pid_t p1, p2;
    time_t debut, fin;

    debut = time(NULL);

   
    p1 = fork();

    if (p1 < 0) 
    {
        printf("Erreur lors de la creation du processus fils 1\n");
        exit(1);
    }

    if (p1 == 0) 
    {
        
        srand(getpid()); 
        int d1 = (rand() % 10) + 1;
        printf("Fils 1 (PID %d) : je vais dormir %d secondes.\n", getpid(), d1);
        sleep(d1);
        printf("Fils 1 terminé.\n");
        exit(0);
    } 
    else
    {
       
        p2 = fork();

        if (p2 < 0) 
        {
            printf("Erreur lors de la creation du processus fils 2\n");
            exit(1);
        }

        if (p2 == 0) 
        {
           
            srand(getpid() + 1); 
            int d2 = (rand() % 10) + 1; 
            printf("Fils 2 (PID %d) : je vais dormir %d secondes.\n", getpid(), d2);
            sleep(d2);
            printf("Fils 2 terminé.\n");
            exit(0);
        }
    }


    printf("Parent : j'attends la fin des fils...\n");

   
    wait(NULL); 
    wait(NULL);

    
    fin = time(NULL);

    printf("Duree totale ecoulee : %ld secondes.\n", (long)(fin - debut));

    return 0;
}