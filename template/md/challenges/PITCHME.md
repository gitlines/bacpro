## Challenges

@title[Challenges]

- starting from basically zero ... tooling, and external libraries 
- OCD: declaring pointers; asterisk on the left or right?
- double pointers? WTF

@fa[arrow-down text-black]

@snap[north-east template-note text-white]
Challenges Main
@snapend

@title[Newer API]

```C
    // First: load up all the address structs with getaddrinfo()
    // improved way of configuring the server
    // where servinfo is basically a linked list that contains all of the address information. The &servinfo is a node
    if ((rv = getaddrinfo(NULL, PORT, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }
```

@snap[north-east template-note text-white]
Newer API
@snapend

@title[Pointer to Pointers]

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

@snap[north-east template-note text-white]
Pointer2Pointer
@snapend



