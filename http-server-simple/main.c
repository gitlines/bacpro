// Server side C program to demonstrate Socket programming

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

// how many pending connections queue will hold
#define BACKLOG 10

int main(int argc, char const *argv[]) {

    // listen on server_fd, new connection on new_fd
    int server_fd, new_fd;
    // needed for reading client request
    long read_values;
    // the port users will be connecting to
    const int PORT = 80;
    struct sockaddr_in addr;
    int addrlen = sizeof(addr);

    // creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Error in socket creation");
        exit(EXIT_FAILURE);
    }

    // configure socket addr struct
    addr.sin_family = AF_INET;
    // convert long integer to a network representation
    addr.sin_addr.s_addr = INADDR_ANY;
    // convert to a network representation
    addr.sin_port = htons(PORT);

    // ensure its set to zero
    memset(addr.sin_zero, '\0', sizeof addr.sin_zero);

    // associate socket with a specific port on the machine, which is necessary in order to listen
    // server_fd is file descriptor; bind IP to host
    if (bind(server_fd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("Error in socket binding");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, BACKLOG) < 0) {
        perror("In listen");
        exit(EXIT_FAILURE);
    }

    // building response: meet minimal HTTP protocol requirements such that browser will actually understand the server response
    char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";

    while (1) {
        printf("\n------------------waiting for connections-------------------\n");
        if ((new_fd = accept(server_fd, (struct sockaddr *) &addr, (socklen_t *) &addrlen)) < 0) {
            perror("Error in accepting connections");
            exit(EXIT_FAILURE);
        }
        // make client/ request information visible in terminal
        char buffer[30000] = {0};
        read_values = read(new_fd, buffer, 30000);
        printf("%s\n", buffer);

        // send response to client
        write(new_fd, response, strlen(response));
        printf("------------------message sent-------------------\n");
        close(new_fd);
    }
    return 0;
}