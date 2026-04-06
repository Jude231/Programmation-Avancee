#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid1 , pid2 ;
    pid1 = fork() ;
    if(pid1 == -1)
    {
        printf("Erreur lors de la création du processus ") ;
        exit(1) ;
    }
    else if(pid1 == 0)
    {
        printf("Je suis le fils 1 \n") ;
    }
    else
    {
        pid2 = fork() ;
        if(pid2 == -1)
        {
            printf("Erreur lors de la création du processus ") ;
            exit(1) ;
        }
        else if(pid2 == 0)
        {
            printf("Je suis le fils 2 \n") ;
        }
        else
        {
            printf("Je suis le père \n") ;
        }
    }
}