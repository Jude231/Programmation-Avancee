#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handler(int sig) 
{
    FILE *f = fopen("/tmp/entier.txt", "r");
    int n;
    if (f) 
    {
        fscanf(f, "%d", &n);
        printf("\n[Affiche] Signal reçu ! Valeur lue : %d\n", n);
        fclose(f);
    }
}

int main() 
{
    // Sauvegarde du PID pour que 'saisit' puisse nous trouver
    FILE *f_pid = fopen("/tmp/affiche.pid", "w");
    fprintf(f_pid, "%d", getpid());
    fclose(f_pid);

    signal(SIGUSR1, handler);
    printf("En attente du signal (PID: %d)...\n", getpid());

    while(1) 
    {
        pause(); // Attend un signal
    }
    return 0;
}