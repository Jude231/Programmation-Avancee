#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() 
{
    struct stat st;
    if (stat("data.bin", &st) != 0) 
    {
        return 1;
    }

    int n = st.st_size / sizeof(int);
    int *tab = malloc(st.st_size);

    FILE *f = fopen("data.bin", "rb");
    fread(tab, sizeof(int), n, f);
    fclose(f);

    printf("Lu %d éléments : ", n);
    for(int i=0; i<n; i++) 
    {
        printf("%d ", tab[i]);
    }
    free(tab);
    return 0;
}