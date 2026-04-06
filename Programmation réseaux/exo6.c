#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int clients[100];
int nb_clients = 0;
pthread_mutex_t mutex_parole = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_liste = PTHREAD_MUTEX_INITIALIZER;

void* gerer_client(void* arg) 
{
    int sock = *((int*)arg);
    struct sockaddr_in addr;
    socklen_t addr_size = sizeof(struct sockaddr_in);
    getpeername(sock, (struct sockaddr*)&addr, &addr_size);
    char *ip = inet_ntoa(addr.sin_addr);

    while (1) 
    {
        char buffer[1024];
        dprintf(sock, "Tapez 1 pour demander la parole : ");
        if (read(sock, buffer, 1024) <= 0) 
        {
            break;
        }
        if (buffer[0] == '1') 
        {
            dprintf(sock, "Attente du tour...\n");
            pthread_mutex_lock(&mutex_parole); // Prend le micro
            
            dprintf(sock, "Vous avez la parole. Votre message : ");
            int n = read(sock, buffer, 1024);
            buffer[n] = '\0';

            // Diffusion à tous
            pthread_mutex_lock(&mutex_liste);
            for (int i = 0; i < nb_clients; i++) 
            {
                if (clients[i] != sock) 
                {
                    dprintf(clients[i], "\n[%s] dit : %s", ip, buffer);
                }
            }
            pthread_mutex_unlock(&mutex_liste);

            pthread_mutex_unlock(&mutex_parole); // Relâche le micro
        }
    }
    close(sock);
    return NULL;
}

int main() 
{
    int serv = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {AF_INET, htons(8080), INADDR_ANY};
    bind(serv, (struct sockaddr*)&adr, sizeof(adr));
    listen(serv, 10);

    while (1) 
    {
        int cli = accept(serv, NULL, NULL);
        pthread_mutex_lock(&mutex_liste);
        clients[nb_clients++] = cli;
        pthread_mutex_unlock(&mutex_liste);

        pthread_t t;
        pthread_create(&t, NULL, gerer_client, &cli);
    }
    return 0;
}