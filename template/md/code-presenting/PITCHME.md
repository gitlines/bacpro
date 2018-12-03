# Code

@fa[arrow-down text-black]

+++?code=template/src/c/main.c&lang=c
@title[Source File]

@[1-15]

@[15-23](declaring .... also: **server_fd** is a file descriptor)

@[21](enables OS read bytes that identify the address family corresponds to socket that is set up)

@[24, 25-28](create socket fd via system call)

@[24, 25-28](**domain:** AF_INET (IP), AF_INET6 (IPv6), AF_UNIX)

@[24, 25-28](**type:** SOCK_STREAM (=TCP), SOCK_DGRAM (=UDP))

@[24, 25-28](**protocol:** not 0 only when IP address family has variations)

@[30-38](configure socket addr struct in in correspondence with socket settings)

@[42-44](associate socket with a port on local machine -> needed in order to listen() for incoming connections on a specific port -> kernel uses port number to match incoming packet to process's socket descriptor

@[46-49](wait for incoming connections and handle them)

@[42-44](wait for incoming connections and handle them)

@[51, 54-59](original socket for listening is only for accepting connections, not for exchanging data)

@[51, 60-71]



# Challenges

@title[Challenges]

- starting from basically zero ... tooling, and external libraries 
- OCD: declaring pointers; asterisk on the left or right?
- double pointers? WTF

@fa[arrow-down text-black]

+++?code=template/src/c/main.c&lang=c

```C
    // First: load up all the address structs with getaddrinfo()
    // improved way of configuring the server
    // where servinfo is basically a linked list that contains all of the address information. The &servinfo is a node
    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }
```

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



