#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define MAX 80
#define PORT 3913
#define SAI struct sockaddr_in
#define SA struct sockaddr

void chat(int connfd)
{
    char buff[MAX];
    int n;

    while (1)
    {
        bzero(buff, MAX);

        read(connfd, buff, sizeof(buff));
        printf("Client: %s", buff);

        if ((strncmp(buff, "exit", 4)) == 0)
        {
            printf("Client exited.Disconnecting Server.\n");
            break;
        }

        n = 0;
        bzero(buff, MAX);
        printf("Server: ");
        while ((buff[n++] = getchar()) != '\n')
            ;
        write(connfd, buff, sizeof(buff));

        if ((strncmp(buff, "exit", 4)) == 0)
        {
            printf("Server exiting\n");
            break;
        }
    }
}
int main()
{
    int sockfd, connfd, len;
    SAI client, server;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
        printf("Error creating socket\n");
    else
        printf("Socket created successfully\n");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);

    if ((bind(sockfd, (SA *)&server, sizeof(server))) == 0)
        printf("Binding successfull\n");

    if ((listen(sockfd, 5)) == 0)
        printf("Server is listening..\n");

    len = sizeof(client);

    connfd = accept(sockfd, (SA *)&client, (socklen_t *)&len);
    printf("Server accepted the client\n");

    chat(connfd);

    close(connfd);
    close(sockfd);

    return 0;
}