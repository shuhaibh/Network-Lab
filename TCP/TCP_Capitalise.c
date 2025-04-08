#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/xinet.h>
#include<ctype.h>
#include<string.h>

#define MAX 80
#define PORT 3913
#define SAI struct sockaddr_in
#define SA struct sockaddr

void process_data(char *input,char *output)
{
    int i = 0;
    int capitalize = 1;

    while (input[i]) {
        if (capitalize && isalpha(input[i])) {
            output[i] = toupper(input[i]);
            capitalize = 0;
        } else {
            output[i] = input[i];
        }

        if (isspace(input[i]))
            capitalize = 1;

        i++;
    }
    output[i] = '\0';
}
void chat(int connfd)
{
        char buff[MAX],result[MAX];
        int n;

        while(1)
        {
                bzero(buff,MAX);
                bzero(result,MAX);

                read(connfd,buff,sizeof(buff));
                printf("Client: %s",buff);

                if((strncmp(buff,"exit",4))==0)
                {
                        printf("Client exited.Disconnecting Server.\n");
                        break;
                }

                process_data(buff,result);

                write(connfd,result,sizeof(result));
        }
}
int main()
{
        int sockfd,connfd,len;
        SAI client,server;

        sockfd = socket(AF_INET,SOCK_STREAM,0);
        if(sockfd == -1)
                printf("Error creating socket\n");
        else
                printf("Socket created successfully\n");

        server.sin_family = AF_INET;
        server.sin_addr.s_addr = htonl(INADDR_ANY);
        server.sin_port = htons(PORT);

        if((bind(sockfd,(SA*)&server,sizeof(server)))==0)
                printf("Binding successfull\n");

        if((listen(sockfd,5))==0)
                printf("Server is listening..\n");

        len = sizeof(client);

        connfd = accept(sockfd,(SA*)&client,(socklen_t*)&len);
        printf("Server accepted the client\n");

        chat(connfd);

        close(connfd);
        close(sockfd);

        return 0;
}