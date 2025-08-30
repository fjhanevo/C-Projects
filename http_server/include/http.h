void handle_http_request(int client_fd);
int parse_request(const char *request, char *method, char *path);
void send_http_response(int client_fd, const char *path);
void send_404_response(int client_fd);
