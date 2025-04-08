#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define MAX 80
#define PORT 3913
#define SA struct sockaddr
#define SAI struct sockaddr_in

void prime(char *input,char *output)
{
        char factors[MAX]="";
        int num = atoi(input);
        if(num<2)
        {
                sprintf(output,"The number is neither prime nor composite\n");
                return;
        }

        int is_prime = 1;
        for(int i=2;i<=(num/2);i++)
        {
                if(num%i==0)
                {
                        is_prime=0;
                        char temp[20];
                        sprintf(temp,"%d ",i);
                        strcat(factors,temp);
                }
        }
        if(is_prime)
        {
                sprintf(output,"The number is a prime number\n");
        }
        else
        {
                sprintf(output,"The number is a composite number and its factors are: %s\n",factors);
        }
}

void chat(int sockfd,SAI client)
{
        char buff[MAX],result[MAX];
        int len = sizeof(client);

        printf("Server ready. Waiting for client...\n");

        while(1)
        {
                bzero(buff,sizeof(buff));
                bzero(result,MAX);

                recvfrom(sockfd,buff,sizeof(buff),0,(SA*)&client,(socklen_t*)&len);
                printf("Client: %s\n",buff);


                if((strncmp(buff,"exit",4))==0)
                {
                        printf("Client Exited..Disconnecting\n");
                        break;
                }

                prime(buff,result);

                sendto(sockfd,result,sizeof(result),0,(SA*)&client,len);
        }
}

int main()
{
        int sockfd;
        SAI server,client;

        sockfd=socket(AF_INET,SOCK_DGRAM,0);

        server.sin_family=AF_INET;
        server.sin_addr.s_addr = htonl(INADDR_ANY);
        server.sin_port = htons(PORT);

        if(bind(sockfd,(SA*)&server,sizeof(server))==0)
                printf("Socket created successfully\n");

        chat(sockfd,client);

        close(sockfd);
        return 0;
}