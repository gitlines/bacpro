// Server side C program to demonstrate Socket programming - IMPROVED

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>


#define PORT "80"  // the port users will be connecting to
#define BACKLOG 10     // how many pending connections queue will hold


// getting sockaddr, either IPv4 or IPv6:
void *get_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in *) sa)->sin_addr);
    }
    return &(((struct sockaddr_in6 *) sa)->sin6_addr);
}

int main(void) {
    int server_fd, new_fd;  // listen on sock_fd, new connection on new_fd

    long read_values;

    struct addrinfo hints, *serv_info, *p;
    struct sockaddr_storage their_addr; // connector's address information
    socklen_t sin_size;
    struct sigaction sa;

    char ipstring[INET6_ADDRSTRLEN];
    int rv;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM; // make sure to use TCP
    hints.ai_flags = AI_PASSIVE; // use my IP

    // First: load up all the address structs with getaddrinfo()
    // improved way of configuring the server
    // where serv_info is basically a linked list that contains all of the address information. The &serv_info is a node
    if ((rv = getaddrinfo(NULL, PORT, &hints, &serv_info)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }
    // looping through results and binding to the very first one
    for (p = serv_info; p != NULL; p = p->ai_next) {
        if ((server_fd = socket(p->ai_family, p->ai_socktype,
                                p->ai_protocol)) == -1) {
            perror("Error in socket creation");
//            exit(EXIT_FAILURE);
            continue;
        }
        // this associates the socket with a specific port on the machine, which is necessary in order to listen
        // sock_fd is the file descriptor, bind the IP to the host running on it, and pass the size of the addr.
        if (bind(server_fd, p->ai_addr, p->ai_addrlen) < 0) {
            close(server_fd);
            perror("Error in bind");
//            exit(EXIT_FAILURE);
            continue;
        }
        break;
    }

    // cleaning up this struct.
    freeaddrinfo(serv_info);

    // some error handling
    if (p == NULL) {
        fprintf(stderr, "Error in binding server\n");
        exit(1);
    }
    if (listen(server_fd, BACKLOG) < 0) {
        perror("Error in listening\n");
        exit(1);
    }
    printf("------------------waiting for connections-------------------\n");

    // building a response
    // meet minimal HTTP protocol requirements such that browser will actually understand the server response
    char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";

    // starting the accept() loop
    while (1) {
        sin_size = sizeof their_addr;
        new_fd = accept(server_fd, (struct sockaddr *) &their_addr, &sin_size);

        if (new_fd < 0) {
            perror("Error in accepting connections");
            continue;
        }
        printf("The server server is now connected to %s\n", ipstring);

        // ntop means network to presentation
        inet_ntop(their_addr.ss_family,
                  get_addr((struct sockaddr *) &their_addr),
                  ipstring, sizeof ipstring);

        // make client/ request information visible in terminal
        char buffer[30000] = {0};
        read_values = recv(new_fd, buffer, 30000, 0);
        printf("%s\n", buffer);

        // child process
        if (!fork()) {
            // child does not need the listener
            close(server_fd);
            // sending the msg
            printf("------------------message sent-------------------\n\n");
            if (send(new_fd, response, strlen(response), 0) < 0)
                perror("Error in sending");
            close(new_fd);
            exit(0);
        }
        close(new_fd);
    }
    return 0;
}