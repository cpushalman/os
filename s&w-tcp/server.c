#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int server_fd, client;
    char buffer[1024];

    struct sockaddr_in server, client_addr;
    socklen_t len = sizeof(client_addr);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&server, sizeof(server));
    listen(server_fd, 5);

    printf("Server waiting...\n");

    client = accept(server_fd,
                    (struct sockaddr *)&client_addr,
                    &len);

    while (1) {
        int n = recv(client, buffer, sizeof(buffer) - 1, 0);

        if (n <= 0)
            break;

        buffer[n] = '\0';

        printf("Received: %s\n", buffer);

        send(client, "ACK", 3, 0);
    }

    close(client);
    close(server_fd);

    return 0;
}