#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() 
{
    int p[2];
    pipe(p);

    if (fork() == 0) 
    {
        char fd_str[10]; 
        sprintf(fd_str, "%d", p[0]);
        
        
        setenv("MON_TUBE", fd_str, 1);
        
        char *args[] = {"./fils_env", NULL};
        execv(args[0], args);
        exit(1);
    } 
    else 
    {
        close(p[0]);
        char *msg = "Message via environnement";
        write(p[1], msg, strlen(msg) + 1);
        close(p[1]);
        wait(NULL);
    }
    return 0;
}