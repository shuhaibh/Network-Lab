
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<string.h>

#define MAX 80
#define PORT 3913
#define SAI struct sockaddr_in
#define SA struct sockaddr

void process_data(char *input,char *output)
{
        int r1,r2,c1,c2;
        int A[10][10],B[10][10],C[10][10];
        int idx = 0,nums[100],count=0;

        char *token = strtok(input," ");
        while(token)
        {
                nums[count++]=atoi(token);
                token = strtok(NULL," ");
        }

        r1=nums[0];
        c1=nums[1];
        r2=nums[2];
        c2=nums[3];

        if(c1!=r2)
        {
                strcpy(output,"Matrix Multiplication not possible");
                return;
        }

        int ptr=4;

        for(int i=0;i<r1;i++)
                for(int j=0;j<c1;j++)
                        A[i][j]=nums[ptr++];

        for(int i=0;i<r2;i++)
                for(int j=0;j<c2;j++)
                        B[i][j]=nums[ptr++];

        for(int i=0;i<r1;i++)
        {
                for(int j=0;j<c2;j++)
                {
                        C[i][j]=0;
                        for(int k=0;k<c1;k++)
                        {
                                C[i][j] += A[i][k]*B[k][j];
                        }
                }
        }

        char temp[50];

        strcpy(output,"Result:\n");
        for(int i=0;i<r1;i++)
        {
                for(int j=0;j<c2;j++)
                {
                        sprintf(temp,"%d ",C[i][j]);
                        strcat(output,temp);
                }
                strcat(output,"\n");
        }
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