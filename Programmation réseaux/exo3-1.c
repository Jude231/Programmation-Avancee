#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
        struct sockaddr_in c_addr;
        socklen_t len = sizeof(c_addr);
        int cli = accept(serv, (struct sockaddr*)&c_addr, &len);

        // Gestion de la date
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        char nom_fich[256];
        
        // Formatage du nom : /home/save/IP_AAAA_MM_JJ.txt
        sprintf(nom_fich, "/home/save/%s_%04d_%02d_%02d.txt", inet_ntoa(c_addr.sin_addr), tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday);

        FILE *f = fopen(nom_fich, "w");
        char buffer[1024];
        int n;
        while ((n = read(cli, buffer, 1024)) > 0) 
        {
            fwrite(buffer, 1, n, f);
        }
        
        fclose(f);
        close(cli);
        printf("Fichier sauvegardé : %s\n", nom_fich);
    }
    return 0;
}