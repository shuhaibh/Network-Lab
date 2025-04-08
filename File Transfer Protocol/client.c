#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#define MAX 4096
#define PORT 3913
#define SA struct sockaddr
#define SAI struct sockaddr_in

int main()
{
        int sockfd,file_size;
        SAI server;
        char filebuff[MAX];
        FILE *fp;
        char filename[100];

        printf("Enter the file name:");
        scanf("%s",filename);

        fp=fopen(filename,"r");
        file_size = fread(filebuff,1,MAX,fp);
        fclose(fp);

        sockfd = socket(AF_INET,SOCK_STREAM,0);
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = htonl(INADDR_ANY);
        server.sin_port = htons(PORT);

        connect(sockfd,(SA*)&server,sizeof(server));

        int net_size = htonl(file_size);
        write(sockfd,&net_size,sizeof(net_size));

        write(sockfd, filebuff, file_size);

        int recv_size;
        read(sockfd,&recv_size,sizeof(recv_size));
        recv_size=ntohl(recv_size);

        int total_recieved = 0;
        while(total_recieved < recv_size)
        {
                int bytes = read(sockfd,filebuff + total_recieved ,recv_size-total_recieved);
                total_recieved += bytes;
        }

        printf("Reversed file content:\n");
        fwrite(filebuff,1,recv_size,stdout);
        printf("\n");

        close(sockfd);
        return 0;
}