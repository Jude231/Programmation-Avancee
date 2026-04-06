#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() 
{
    
    char *env_val = getenv("MON_TUBE");
    
    if (env_val == NULL) return 1;

    int fd_lecture = atoi(env_val);
    char tampon[100];

    read(fd_lecture, tampon, 100);
    printf("Fils (via ENV) a reçu : %s\n", tampon);

    close(fd_lecture);
    return 0;
}