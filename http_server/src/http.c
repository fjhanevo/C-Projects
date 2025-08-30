#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include "http.h"

#define BUF_SIZE 8192
#define METHOD_SIZE 16
#define PATH_SIZE 256
#define HEAD_SIZE 1024
#define FILE_SIZE 4096

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
        send_200_response(client_fd, file, file_path);
        fclose(file);
    }
}

void send_404_response(int client_fd)
{
    const char *response_404 = "HTTP/1.0 404 Not Found\n\n";

    send(client_fd, response_404, strlen(response_404), 0);
}

// helper function to get the mime type from the extension
const char *get_mime_type(const char *file_path)
{
    if (strstr(file_path, ".html")) return "text/html";
    if (strstr(file_path, ".css")) return "text/css";
    if (strstr(file_path, ".js")) return "application/javascript";
    if (strstr(file_path, ".jpg")) return "image/jpg";
    if (strstr(file_path, ".png")) return "image/png";

    // Default return type
    return "application/octet-stream";
}

void send_200_response(int client_fd, FILE *file, const char *file_path)
{
    // go to EOF
    fseek(file, 0, SEEK_END);
    // get the current position
    long file_size = ftell(file); 
    // go to beginning of file
    fseek(file, 0, SEEK_SET);

    const char* mime_type = get_mime_type(file_path);

    // construct and send headers
    char header_buffer[HEAD_SIZE];
    sprintf(header_buffer,
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: %s\r\n"
            "Content-Length: %ld\r\n"
            "\r\n", mime_type, file_size);

    send(client_fd, header_buffer, strlen(header_buffer), 0);

    // send the file content in chunks
    char file_buffer[FILE_SIZE];
    size_t bytes_read;

    // read from file and send to the socket
    while ((bytes_read = fread(file_buffer, 1, sizeof(file_buffer), file)) > 0) {
        send(client_fd, file_buffer, bytes_read, 0);
    }

}
