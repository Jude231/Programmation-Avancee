#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

void relay(int de, int vers) 
{
    char buffer[1024] = {0};
    dprintf(vers, "L'autre client écrit...\n");
    dprintf(de, "Saisissez la réponse : ");
    int n = read(de, buffer, 1024);
    if (n > 0) 
    {
        dprintf(vers, "L'autre client dit : %s", buffer);
    }
}

int main() 
{
    int serv = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {AF_INET, htons(8080), INADDR_ANY};
    bind(serv, (struct sockaddr*)&addr, sizeof(addr));
    listen(serv, 2);

    printf("En attente de deux clients...\n");
    int c1 = accept(serv, NULL, NULL);
    printf("Client 1 connecté. En attente du second...\n");
    int c2 = accept(serv, NULL, NULL);
    printf("Match ! Début de la conversation.\n");

    dprintf(c1, "Connecté ! Vous commencez.\n");
    dprintf(c2, "Connecté ! Attendez le message de l'autre...\n");

    while (1) 
    {
        relay(c1, c2);
        relay(c2, c1);
    }

    return 0;
}