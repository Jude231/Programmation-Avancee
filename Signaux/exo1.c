#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main() 
{
    pid_t pid = fork();

    if (pid == 0) 
    {
        // Le fils : calcul sans fin
        while (1) 
        {
            printf("Fils en cours de calcul...\n");
            sleep(1);
        }
    } 
    else 
    {
        // Le père : menu de contrôle
        char choix;
        while (1) 
        {
            printf("\nMenu : [s]toper, [r]edémarrer, [q]uitter : ");
            scanf(" %c", &choix);

            if (choix == 's') 
            {
                kill(pid, SIGSTOP);
                printf("Fils endormi.\n");
            } 
            else if (choix == 'r') 
            {
                kill(pid, SIGCONT);
                printf("Fils redémarré.\n");
            } 
            else if (choix == 'q') 
            {
                kill(pid, SIGKILL);
                printf("Fils tué. Fin du programme.\n");
                wait(NULL); // Nettoyage du processus zombie
                break;
            }
        }
    }
    return 0;
}