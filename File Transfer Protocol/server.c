#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define MAX 4096
#define PORT 3913
#define SA struct sockaddr
#define SAI struct sockaddr_in

int main()
{
        int sockfd,newsockfd,len;
        SAI server,client;
        char buff[MAX];
        int file_size,total_bytes,bytes_read;

        sockfd = socket(AF_INET, SOCK_STREAM, 0);

        server.sin_family = AF_INET;
        server.sin_addr.s_addr = htonl(INADDR_ANY);
        server.sin_port = htons(PORT);

        bind(sockfd,(SA*)&server,sizeof(server));
        listen(sockfd,5);

        len=sizeof(client);

        newsockfd = accept(sockfd,(SA*)&client,&len);

        read(newsockfd,&file_size,sizeof(file_size));
        file_size = htonl(file_size);

        total_bytes = 0;
        while(total_bytes<file_size)
        {
                bytes_read= read(newsockfd,buff+total_bytes,file_size-total_bytes);
                total_bytes += bytes_read;
        }

        for(int i=0;i<total_bytes;i++)
        {
                char temp = buff[i];
                buff[i] = buff[total_bytes - i - 1];
                buff[total_bytes - i - 1] = temp;
        }

        int net_size = htonl(total_bytes);
        write(newsockfd,&net_size,sizeof(net_size));
        write(newsockfd,buff,total_bytes);

        close(newsockfd);
        close(sockfd);

        return 0;
}