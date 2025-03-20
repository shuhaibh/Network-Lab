#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERV_TCP_PORT 5035
#define MAX_BUFFER_SIZE 4096

int main() {
    int sockfd, file_size;
    struct sockaddr_in serv_addr;
    char file_buffer[MAX_BUFFER_SIZE];
    FILE *fp;
    char file_name[100];

    // Prompt user for file name and read it
    printf("Enter the source file name: ");
    scanf("%s", file_name);

    // Open file and read its contents into file_buffer
    fp = fopen(file_name, "r");
    file_size = fread(file_buffer, 1, MAX_BUFFER_SIZE, fp);
    fclose(fp);

    // Create a socket and connect to the server
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(SERV_TCP_PORT);
    connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    // Send the file size (converted to network byte order)
    int net_size = htonl(file_size);
    write(sockfd, &net_size, sizeof(net_size));

    // Send the file content
    write(sockfd, file_buffer, file_size);

    // Receive the reversed file content size first
    int recv_size;
    read(sockfd, &recv_size, sizeof(recv_size));
    recv_size = ntohl(recv_size);

    // Then receive the reversed file content
    int total_received = 0, bytes;
    while(total_received < recv_size) {
        bytes = read(sockfd, file_buffer + total_received, recv_size - total_received);
        total_received += bytes;
    }

    // Print the reversed file content
    printf("Reversed file content:\n");
    fwrite(file_buffer, 1, recv_size, stdout);
    printf("\n");

    close(sockfd);
    return 0;
}
