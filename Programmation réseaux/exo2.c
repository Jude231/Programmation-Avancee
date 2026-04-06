#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

void verifier_et_saluer(int clisock, char *ip_client) 
{
    FILE *f = fopen("add_autoris.txt", "r");
    char ip_auth[20], nom[50];
    int autorise = 0;

    if (f) 
    {
        while (fscanf(f, "%s %s", ip_auth, nom) == 2) 
        {
            if (strcmp(ip_client, ip_auth) == 0) 
            {
                dprintf(clisock, "Bienvenue %s ! Accès accordé.\n", nom);
                autorise = 1;
                break;
            }
        }
        fclose(f);
    }

    if (!autorise) 
    {
        dprintf(clisock, "Erreur : Votre IP (%s) n'est pas autorisée.\n", ip_client);
    }
    close(clisock);
}

int main() 
{
    int serv = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {AF_INET, htons(8080), INADDR_ANY};
    bind(serv, (struct sockaddr*)&addr, sizeof(addr));
    listen(serv, 5);

    printf("Serveur de contrôle d'accès lancé sur le port 8080...\n");

    while (1) 
    {
        struct sockaddr_in client_addr;
        socklen_t len = sizeof(client_addr);
        int cli = accept(serv, (struct sockaddr*)&client_addr, &len);
        
        char *ip_client = inet_ntoa(client_addr.sin_addr);
        printf("Connexion tentée depuis : %s\n", ip_client);
        
        verifier_et_saluer(cli, ip_client);
    }
    return 0;
}