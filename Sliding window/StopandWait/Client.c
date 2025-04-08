#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/time.h>

#define PORT 3913
#define BUFFER_SIZE 1024
#define TIMEOUT 3  // Timeout in seconds

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};
    char packet[50];
    struct timeval tv;

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IP address
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        perror("Invalid address or Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    printf("Client: Connected to server.\n");

    // Set socket timeout
    tv.tv_sec = TIMEOUT;
    tv.tv_usec = 0;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(tv));

    int total_packets;
    printf("Enter the number of packets: ");
    scanf("%d", &total_packets);

    int current_packet = 1;

    while (current_packet <= total_packets) {
        sprintf(packet, "%d", current_packet);
        printf("Client: Sending packet %d...\n", current_packet);
        send(sock, packet, strlen(packet), 0);

        // Wait for ACK
        int valread = read(sock, buffer, BUFFER_SIZE);

        if (valread > 0 && strncmp(buffer, "ACK", 3) == 0) {
            printf("Client: ACK received for packet %d\n\n", current_packet);
            current_packet++;  // move to next only if ACK received
        } else {
            printf("Client: Timeout or ACK lost! Retransmitting packet %d...\n\n", current_packet);
        }

        memset(buffer, 0, BUFFER_SIZE);  // Clear buffer
    }

    printf("Client: All packets sent successfully.\n");
    close(sock);
    return 0;
}