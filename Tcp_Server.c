#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX 80
#define PORT 3913
#define SA struct sockaddr
#define SAI struct sockaddr_in

void chat(int connfd)
{
    char buff[MAX];
    int n;

    while (1)
    {
        bzero(buff, MAX);

        read(connfd, buff, sizeof(buff));
        printf("Client: %s", buff);

        if (strncmp(buff, "Exit", 4) == 0)
        {
            printf("Client Exited.Disconnecting Server!..\n");
            break;
        }

        printf("Server: ");
        bzero(buff, MAX);

        n = 0;
        while ((buff[n++] = getchar()) == '\n')
            ;
        write(connfd, buff, sizeof(buff));

        if (strncmp(buff, "Exit", 4) == 0)
        {
            printf("Server Exited!..\n");
            break;
        }
    }
}

int main()
{
    SAI client, server;
    
}