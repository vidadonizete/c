#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        fprintf(stderr, "Error while creating socket file descriptor");
        exit(0);
    }

    struct sockaddr_in sockaddr_in = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = inet_addr("0.0.0.0"),
        .sin_port = htons(8080),
    };

    if (connect(server_fd, (struct sockaddr *)&sockaddr_in, sizeof(struct sockaddr_in)))
    {
        fprintf(stderr, "Error while opening socket");
        exit(0);
    }

    char buffer[2048];

    for (;;)
    {
        buffer[0] = '\0';
        printf("Client: ");
        fgets(buffer, sizeof(buffer), stdin);
        write(server_fd, buffer, sizeof(buffer));

        buffer[0] = '\0';
        read(server_fd, buffer, sizeof(buffer));
        printf("Server: %s\n", buffer);
    }

    close(server_fd);
    return 0;
}