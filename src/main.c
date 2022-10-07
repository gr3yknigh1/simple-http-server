/* NAME: Simple Http Server
 * LICENSE: No
 * YEAR: 2022
 * AUTHOR: @gr3yknigh1
 * REFERENCE: https://dev-notes.eu/2018/06/http-server-in-c/
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <netdb.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <arpa/inet.h>

#define BACKLOG 10

#define OK 0
#define ERR 1

#define true 1
#define false 0

const int PORT = 8001;

struct __string {
    char* string_data;
    int size;
} String;

int report(struct sockaddr_in *server_address) {
    char host_buffer[INET6_ADDRSTRLEN];
    char service_buffer[NI_MAXSERV];
    socklen_t address_length = sizeof(*server_address);

    int socket_address_translation_error = getnameinfo(
        (struct sockaddr *) server_address,
        address_length,
        host_buffer,
        sizeof(host_buffer),
        service_buffer,
        sizeof(service_buffer),
        NI_NUMERICHOST
    );

    if (socket_address_translation_error != OK) {
        printf("It's not working!!\n");
        return ERR;
    }

    printf("Server listening on http://%s:%d\n", host_buffer, PORT);
    printf("Service Buffer: %s\n", service_buffer);
    return OK;
}

void set_http_header(char http_header[]) {
    FILE *html_data = fopen("public/index.html", "r");

    char line[100];
    char response_data[8000];

    while (fgets(line, 100, html_data) != OK) {
        strcat(response_data, line);
    }

    strcat(http_header, response_data);

    fclose(html_data);
}

// void start_socket_loop(int* server_socket, char* http_header) {
//     int client_socket;
//     while(true) {
//         client_socket = accept(*server_socket, NULL, NULL);
//         send(client_socket, http_header, sizeof(http_header), 0);
//         close(client_socket);
//     }
// }

int main() {
    char http_header[8000] = "HTTP/1.1 200 OK\r\n\n";

    int server_socket = socket(
        AF_INET,
        SOCK_STREAM,
        0
    );

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    int socket_bind_error = bind(
        server_socket,
        (struct sockaddr *) &server_address,
        sizeof(server_address)
    );
    if (socket_bind_error != OK) {
        printf("Socket binding error: %d\n", socket_bind_error);
        return ERR;
    }

    int socket_listening_error = listen(server_socket, BACKLOG);
    if (socket_listening_error < OK) {
        printf(
            "Error: The server is not listening. Error code: %d\n",
            socket_listening_error
        );
        return ERR;
    }


    int reporting_error = report(&server_address);
    if (reporting_error) {
        return ERR;
    }

    set_http_header(http_header);

    int client_socket;
    while(true) {
        client_socket = accept(server_socket, NULL, NULL);
        if (client_socket == -1) {
            printf("Can't accept connection via socket!");
            continue;
        }
        printf("Accepted a connection!\n");
        send(client_socket, http_header, sizeof(http_header), 0);
        close(client_socket);
    }

    return OK;
}

