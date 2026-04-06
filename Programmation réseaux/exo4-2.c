#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <unistd.h>

int main() 
{
    int serv = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {AF_INET, htons(8080), INADDR_ANY};
    bind(serv, (struct sockaddr*)&addr, sizeof(addr));
    listen(serv, 5);

    while (1) 
    {
        int cli = accept(serv, NULL, NULL);
        
        // Réception dans un fichier temporaire
        FILE *f = fopen("/tmp/recu.tgz", "wb");
        char buffer[1024];
        int n;
        while ((n = read(cli, buffer, 1024)) > 0) 
        {
            fwrite(buffer, 1, n, f);
        }
        fclose(f);
        close(cli);

        // Décompression (Simulé dans /tmp pour le test)
        system("mkdir -p /tmp/save && tar -zxvf /tmp/recu.tgz -C /tmp/save/ && rm /tmp/recu.tgz");
        printf("Répertoire extrait dans /tmp/save/\n");
    }
    return 0;
}