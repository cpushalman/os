#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int sock;
    char buffer[1024];
    char message[1024];

    struct sockaddr_in server;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    connect(sock, (struct sockaddr *)&server, sizeof(server));

    for (int i = 1; i <= 5; i++) {

        sprintf(message, "DATA %d", i);

        printf("Sending: %s\n", message);

        send(sock, message, strlen(message), 0);

        int n = recv(sock, buffer, sizeof(buffer) - 1, 0);

        buffer[n] = '\0';

        printf("Received: %s\n\n", buffer);
    }

    close(sock);

    return 0;
}