#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include "http.h"

#define BUF_SIZE 8192
#define METHOD_SIZE 16
#define PATH_SIZE 256

void handle_http_request(int client_fd)
{
    char request_buffer[BUF_SIZE];
    char method[METHOD_SIZE];
    char path[PATH_SIZE];
    
    // read client request
    int bytes_recieved = recv(client_fd, request_buffer, BUF_SIZE - 1, 0);

    if (bytes_recieved < 0) {
        perror("recv failed");
        return;
    }
    // add null terminator
    request_buffer[bytes_recieved] = '\0';

    if (parse_request(request_buffer, method, path) == 0) {
        send_http_response(client_fd, path); 
    }

}

int parse_request(const char *request, char *method, char *path)
{
    // with limits to prevent buffer overflow
    sscanf(request, "%15s %255s", method, path);

    if (strcmp(method, "GET") == 0) {
        return 0;
    }
    return -1;
}

void send_http_response(int client_fd, const char *path)
{
    char file_path[PATH_SIZE];

    // securely create path to avoid overwriting the buffer
    snprintf(file_path, sizeof(file_path), "./public%s", path);

    FILE *file = fopen(file_path, "rb");

    if (file == NULL) {
        send_404_response(client_fd); 
    }
    else {
        // call to send_200_response
        fclose(file);
    }

}
