### HTTP Server in C

#### Motivation

- deeper understanding of network communication, related protocols etc.

---

### OSI Model

- Application Layer
- Presentation Layer
- Session Layer
- **Transport Layer**
- Network Layer
- Data Link
- Physical Layer

<!-- ![OSI Model](https://github.com/gitlines/bac/blob/master/img/osi.jpg) -->

---

### Transport Layer

- provides flow control and error handling, and participates in solving problems TCP, UDP
- TCP = Transmission Control Protocol 
- makes sure data are sent and received in the correct sequence
- HTTP servers use TCP in order to provide reliable transport

---

### Sockets

- aka Berkeley sockets:a Unix API for Internet sockets and Unix domain sockets used for inter-process communication
- mechanism used by operating systems to provide network access to programs
- network agnostic

---

### Code 

- *POSIX C networking APIs* 
- sits between normal programs and the operating system
- usually part of C library implementation

---

### Code 

- **server_fd** is a file descriptor
- **domain:** AF_INET (IP), AF_INET6 (IPv6), AF_UNIX
- **type:** SOCK_STREAM (=TCP), SOCK_DGRAM (=UDP) 
- **protocol:** not 0 only when IP address family has variations

```C
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
```

---

### Code 

- sockaddr: enables OS read bytes that identify the address family 
- corresponds to socket that is set up

```C
    // configure socket addr struct
    addr.sin_family = AF_INET;
    // convert long integer to a network representation
    addr.sin_addr.s_addr = INADDR_ANY;
    // convert to a network representation
    addr.sin_port = htons(PORT);
    // ensure its set to zero
    memset(addr.sin_zero, '\0', sizeof addr.sin_zero);

```

---

### Code 

- bind():
- associate socket with a port on local machine
- needed in order to listen() for incoming connections on a specific port
- kernel uses port number to match incoming packet to process's socket descriptor

- listen() / accept()
- wait for incoming connections and handle them

```C
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
```

---

### Code


<!-- - original socket for listening is only for accepting connections, not for exchanging data
- socket operations are synchronous, or blocking, and accept will block until a connection is present on the queue.
- accept() creates a new socket for that connection -->

```C
    // building response: meet minimal HTTP protocol requirements such that browser will actually understand the server response
    char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
    while (1) {
        if ((new_fd = accept(server_fd, (struct sockaddr *) &addr, (socklen_t *) &addrlen)) < 0) {
            perror("Error in accepting connections");
            exit(EXIT_FAILURE);
        }
        // send response to client
        write(new_fd, response, strlen(response));
        close(new_fd);
    }
    return 0;
```

---

### Challenges

- starting from basically zero ... tooling, and external libraries 
- OCD: declaring pointers; asterisk on the left or right?
- double pointers? WTF

---

### Challenges

```C
    // First: load up all the address structs with getaddrinfo()
    // improved way of configuring the server
    // where servinfo is basically a linked list that contains all of the address information. The &servinfo is a node
    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }
```

---

### Challenges

```C
    // looping through results and binding to the very first one 
    for(p = servinfo; p != NULL; p = p->ai_next) {
        if ((sock_fd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("Error in socket creation");
            exit(EXIT_FAILURE);
            continue;
        }
        // this associates the socket with a specific port on the machine, which is necessary in order to listen
        // sock_fd is the file descriptor, bind the IP to the host running on it, and pass the size of the addr.
        if (bind(sock_fd, p->ai_addr, p->ai_addrlen) < 0) {
            close(sock_fd);
            perror("Error in bind");
//            exit(EXIT_FAILURE);
            continue;
        }
        break;
    }
```

