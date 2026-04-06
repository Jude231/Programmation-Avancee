#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid ;
    int i ;
    pid = fork() ;
    for(i = 0 ; i < 5; i++)
    {
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
    printf("Je suis le père \n") ;
    for(int j = 0 ; j < 5; j++)
    {
        
        wait(NULL) ;
    }
    return 0 ;
}