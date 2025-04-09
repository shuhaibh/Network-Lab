#include <sys/socket.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 6543
#define LOST "127.0.0.1"

void selective(int csd) {
    int size = 4, i, curr = 0;
    char buff[128];
    for(i = 0; i < size; i++) {
        recv(csd, buff, 128, 0);
        printf("RECV << %s\n", buff);
    }

    while(1) {
        if(curr == 4) {
            sprintf(buff, "%dNACK", curr);
            send(csd, buff, 128, 0);
            printf("SEND >> %s\n", buff);
            recv(csd, buff, 128, 0);
            printf("RECV << %s\n", buff);
        }
        sprintf(buff, "%dACK", curr);
        send(csd, buff, 128, 0);
        printf("SEND >> %s\n", buff);
        recv(csd, buff, 128, 0);
        printf("RECV << %s\n", buff);
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

    if(bind(sd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        printf("Binding error.\n");
        return 1;
    }

    listen(sd, 1);

    int csd;
    if((csd = accept(sd, NULL, NULL)) < 0) {
        printf("Could not accept incoming connection.\n");
        return 1;
    }

    selective(csd);

    close(csd);
    close(sd);
    return 0;
}