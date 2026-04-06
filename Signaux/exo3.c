#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handler_fils(int sig) 
{
    printf("\n[Fils %d] Je meurs... Adieu monde cruel !\n", getpid());
    exit(0);
}

void handler_pere(int sig) 
{
    printf("\n[Père] Signal de fin reçu. Fermeture du programme.\n");
    exit(0);
}

int main() 
{
    pid_t pids[5];
    int i, num, action;

    // Installation du handler pour le père (ex: Ctrl+C)
    signal(SIGINT, handler_pere);

    for (i = 0; i < 5; i++) 
    {
        pids[i] = fork();
        if (pids[i] == 0)
        {
            // Code du fils
            signal(SIGTERM, handler_fils); // Intercepte la demande de terminaison
            while (1) 
            {
                pause(); 
            }
        }
    }

    while (1) {
        printf("\n--- MENU PÈRE ---\n1. Endormir (SIGSTOP)\n2. Réveiller (SIGCONT)\n3. Terminer (SIGTERM)\n");
        printf("Choix (Indice_Fils[0-4] Action[1-3]) : ");
        if (scanf("%d %d", &num, &action) != 2) 
        {
            break;
        }
        if (num < 0 || num > 4) 
        {
            continue;
        }
        if (action == 1) 
        {
            kill(pids[num], SIGSTOP);
        }
        else if (action == 2) 
        {
            kill(pids[num], SIGCONT);
        }
        else if (action == 3) 
        {
            kill(pids[num], SIGTERM);
        }
    }

    return 0;
}