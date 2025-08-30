#ifndef HTTP_H
#define HTTP_H

#include <stdio.h>

void handle_http_request(int client_fd);
int parse_request(const char *request, char *method, char *path);
void send_http_response(int client_fd, const char *path);
void send_404_response(int client_fd);
void send_200_response(int client_fd, FILE* file, const char *file_path);

#endif // HTTP_H
