#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[]) 
{
    if (argc < 2) 
    {
        return 1;
    }

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr = {AF_INET, htons(8080)};
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
    
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    FILE *f = fopen(argv[1], "r");
    char buffer[1024];
    int n;
    while ((n = fread(buffer, 1, 1024, f)) > 0) 
    {
        write(sock, buffer, n);
    }

    fclose(f);
    close(sock);
    return 0;
}