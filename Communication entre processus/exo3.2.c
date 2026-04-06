#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{
    if (argc < 2) 
    {
        return 1;
    }
    int fd_lecture = atoi(argv[1]); 
    char tampon[100];

    read(fd_lecture, tampon, 100);
    printf("Fils (execv) a reçu : %s\n", tampon);

    close(fd_lecture);
    return 0;
}