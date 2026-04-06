#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main() 
{
    int n, tab[100];
    printf("Nombre d'éléments : ");
    scanf("%d", &n);
    for(int i=0; i<n; i++) 
    {
        scanf("%d", &tab[i]);
    }

    // Ouverture avec permissions : rw-rw-r-- (0664)
    int fd = open("data.bin", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR|S_IWUSR|S_IWGRP|S_IRGRP|S_IROTH);
    write(fd, tab, n * sizeof(int));
    close(fd);
    return 0;
}