#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main() 
{
    int n, pid_dest;
    printf("Entrez un entier : ");
    scanf("%d", &n);

    // Écriture de la donnée
    FILE *f = fopen("/tmp/entier.txt", "w");
    fprintf(f, "%d", n);
    fclose(f);

    // Lecture du PID du destinataire
    FILE *f_pid = fopen("/tmp/affiche.pid", "r");
    if (f_pid) 
    {
        fscanf(f_pid, "%d", &pid_dest);
        fclose(f_pid);
        kill(pid_dest, SIGUSR1); 
    }
    return 0;
}