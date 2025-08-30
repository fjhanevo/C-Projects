#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "server.h"
#include "http.h"

#define PORT 8080

int listening_socket(int port)
{
    int server_fd;
    int opt = 1;
    struct sockaddr_in addr;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("listening socket failed!");
        return -1;
    }

    // attach socket to PORT
    if (setsockopt(server_fd, SOL_SOCKET, 
                   SO_REUSEADDR | SO_REUSEPORT, 
                   &opt, sizeof(opt))) {
        perror("setockopt");
        return -1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    // bind the socket
    if (bind(server_fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("bind failed!");
        return -1;
    }

    // put socket into listening mode
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        return -1;
    }

    return server_fd;
}

void run_server(int server_fd)
{
    int client_fd;    
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr); 

    while (1) {
        if ((client_fd = accept(server_fd, (struct sockaddr*)&addr, &addrlen)) < 0) {
            perror("accept");
            continue; 
        }
        handle_http_request(client_fd);
        close(client_fd);
    }
}
