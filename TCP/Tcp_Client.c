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

void chat(int sockfd)
{
        char buff[MAX];
        int n;

        while(1)
        {
                bzero(buff, sizeof(buff));

                n=0;

                printf("Client: ");
                while ((buff[n++] = getchar()) != '\n');
                write(sockfd, buff, sizeof(buff));

                if ((strncmp(buff, "exit", 4)) == 0)
                {
                        printf("Client Exiting...\n");
                        break;
                }

                bzero(buff,sizeof(buff));

                read(sockfd,buff,sizeof(buff));
                printf("Server: %s",buff);

                if ((strncmp(buff, "exit", 4)) == 0)
                {
                        printf("Server Exited.diconnecting client...\n");
                        break;
                }
        }
}

int main()
{
        SAI server;
        int sockfd;

        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        printf("Socket created successfully\n");

        bzero(&server,sizeof(server));

        server.sin_family = AF_INET;
        server.sin_addr.s_addr = htonl(INADDR_ANY);
        server.sin_port = htons(PORT);

        if (connect(sockfd,(SA*)&server,sizeof(server))==0);
                printf("Connected to server\n");

        chat(sockfd);
        close(sockfd);

        return 0;
}