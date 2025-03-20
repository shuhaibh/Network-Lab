#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERV_TCP_PORT 5035
#define MAX_BUFFER_SIZE 4096

int main() {
    int sockfd, newsockfd, clength;
    struct sockaddr_in serv_addr, cli_addr;
    char buffer[MAX_BUFFER_SIZE];
    int file_size, total_bytes, bytes_read;

    // Create socket, bind, and listen
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(SERV_TCP_PORT);
    bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(sockfd, 5);
    clength = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clength);

    // First, read the file size (sent as an int in network order)
    read(newsockfd, &file_size, sizeof(file_size));
    file_size = ntohl(file_size);

    // Read the file content from the client
    total_bytes = 0;
    while(total_bytes < file_size) {
        bytes_read = read(newsockfd, buffer + total_bytes, file_size - total_bytes);
        total_bytes += bytes_read;
    }

    // Reverse the file content in place
    for (int i = 0; i < total_bytes / 2; i++) {
        char temp = buffer[i];
        buffer[i] = buffer[total_bytes - i - 1];
        buffer[total_bytes - i - 1] = temp;
    }

    // Send the reversed content back:
    // First, send the size of the reversed content (same as file_size)
    int net_size = htonl(total_bytes);
    write(newsockfd, &net_size, sizeof(net_size));
    // Then send the reversed content
    write(newsockfd, buffer, total_bytes);

    close(newsockfd);
    close(sockfd);
    return 0;
}
