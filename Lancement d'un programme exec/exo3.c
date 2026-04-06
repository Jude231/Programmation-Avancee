#include <unistd.h>
#include <stdio.h>

int main() 
{
    char fichier[100];

    printf("Nom du fichier : ");
    scanf("%s", fichier);
    execl("/usr/bin/emacs", "emacs", fichier, NULL);

    return 0;
}