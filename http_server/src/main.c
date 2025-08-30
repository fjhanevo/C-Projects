#include <stdio.h>
#include <stdlib.h>
#include "server.h"

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        return 1;
    }

    int port = atoi(argv[1]);
    int server_fd = listening_socket(port);
    if (server_fd < 0) {
        fprintf(stderr, "Failed to create listening socket\n");
        return 1;
    }

    printf("Server listening on port: %d\n", port);
    run_server(server_fd);

    return 0;
}


