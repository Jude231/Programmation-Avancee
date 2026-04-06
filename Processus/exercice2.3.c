#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int i ;
    pid_t pid ;
    for(i = 0 ; i < 5; i++)
    {
        pid = fork() ;
        if(pid == -1)
        {
            printf("Erreur lors de la création du processus ") ;
            exit(1) ;
        }
        else if(pid == 0)
        {
            printf("Je suis le fils %d \n", i+1) ;
            break ;
        }
    }
    return 0;

        
}