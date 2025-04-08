#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX 80
#define PORT 3913
#define SA struct sockaddr
#define SAI struct sockaddr_in

void chat(int sockfd,SAI server)
{
        printf("Client ready..\n");

        char buff[MAX];
        int len = sizeof(server);

        while(1)
        {
                bzero(buff,sizeof(buff));
                printf("Enter the number to check: ");
                fgets(buff,sizeof(buff),stdin);

                buff[strcspn(buff,"\n")]='\0';

                sendto(sockfd,buff,sizeof(buff),0,(SA*)&server,len);

                if (strncmp(buff, "exit", 4) == 0)
                {
                        printf("Client Exit...\n");
                        break;
                }

                bzero(buff,sizeof(buff));
                recvfrom(sockfd,buff,sizeof(buff),0,(SA*)&server,(socklen_t*)&len);

                printf("Server: %s",buff);
        }
}

int main()
{
        SAI server;
        int sockfd;

        sockfd=socket(AF_INET,SOCK_DGRAM,0);

        server.sin_family = AF_INET;
        server.sin_addr.s_addr = htonl(INADDR_ANY);
        server.sin_port = htons(PORT);

        chat(sockfd,server);

        close(sockfd);
        return 0;
}