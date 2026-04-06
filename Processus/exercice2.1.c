#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid ;
    pid = fork() ;

    if(pid == -1)
    {
        perror("Erreur lors de la création du processus ") ;
        exit(1) ;
    }
    else if(pid == 0)
    {
        printf("Je suis fils \n") ;
    }
    else
    {
        printf("Je suis le père \n") ;
    }
}
