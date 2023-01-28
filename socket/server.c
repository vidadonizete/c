#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        fprintf(stderr, "Error while creating socket file descriptor");
        exit(0);
    }

    struct sockaddr_in server_socket = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = inet_addr("0.0.0.0"),
        .sin_port = htons(8080),
    };

    if (bind(server_fd, (struct sockaddr *)&server_socket, sizeof(struct sockaddr_in)))
    {
        fprintf(stderr, "Error while bind socket");
        exit(0);
    }

    if (listen(server_fd, /*connections*/ 1))
    {
        fprintf(stderr, "Error while listen socket");
        exit(0);
    }

    struct sockaddr client_socket;
    int client_socket_length;
    int client_fd = accept(server_fd, (struct sockaddr *)&server_socket, &client_socket_length);

    if (client_fd < 0)
    {
        fprintf(stderr, "Error while connect client");
        exit(0);
    }

    char buffer[2048];

    for (;;)
    {
        buffer[0] = '\0';
        read(client_fd, buffer, sizeof(buffer));
        printf("Client: %s\n", buffer);

        buffer[0] = '\0';
        printf("Server: ");
        fgets(buffer, sizeof(buffer), stdin);
        write(client_fd, buffer, sizeof(buffer));
    }

    close(client_fd);
    close(server_fd);

    return 0;
}