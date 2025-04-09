#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 6543
#define LOST "127.0.0.1"

void selective(int csd) {
    char data[128][128], buff[128];
    int curr, size = 4, i;
    for(curr = 0; curr < size; curr++) {
        printf("SEND << ");
        scanf("%s", data[curr]);
        send(csd, data[curr], 128, 0);
    }

    while(1) {
        recv(csd, buff, 128, 0);
        printf("RECV >> %s\n", buff);
        if(buff[1] == 'N') {
            send(csd, data[curr - size], 128, 0);
            printf("RESE: %s\n", data[curr - size]);
            continue;
        }
        printf("SEND << ");
        scanf("%s", data[curr]);
        send(csd, data[curr], 128, 0);
        curr++;
    }
}

int main() {
    int sd;
    if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation error.\n");
        return 1;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(LOST);

    if(connect(sd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Connection Error\n");
        return 1;
    }

    selective(sd);

    close(sd);
    return 0;
}