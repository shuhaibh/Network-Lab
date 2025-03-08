#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr
#define SAI struct sockaddr_in

void chat(int sockfd, SAI client)
{
    printf("Server ready. Waiting for client..\n");
    char buff[MAX];
    int n,len=sizeof(client);

    while (condition)
    {
        bzero(buff, sizeof(buff));

        recvfrom(sockfd, buff, sizeof(buff), 0, (SA *)&client, (socketlen_t *)&len);
        printf("Client: %s", buff);

        if (strncmp(buff, "exit", 4) == 0) 
        {
            printf("Client disconnected. Server shutting down...\n");
            break;
        }

        printf("\nServer: ");
        bzero(buff, sizeof(buff));
        n = 0;
        while ((buff[n++] = getchar()) != '\n'); 

        sendto(sockfd, buff, sizeof(buff), 0, (SA*)&client, len);

        if (strncmp(buff, "exit", 4) == 0)
        {
            printf("Server Exit...\n");
            break;
        }     
    }
}

int main() 
{
    SAI server, client;
    int sockfd; 

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;             
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);          

    if ((bind(sockfd, (SA*)&server, sizeof(server))) == 0) 
        printf("Socket successfully binded..\n");

    chat(sockfd, client);

    close(sockfd);
    return 0;
}