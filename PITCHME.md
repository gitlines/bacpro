---?color=linear-gradient(to right, #c02425, #f0cb35)
@title[Introduction]

@snap[west headline text-white span-70]
HTTP Server in C
@snapend

@snap[south-west byline  text-white]
Philipp Messerschmidt - cs16-1/WS2018
@snapend

---

@title[Motivation]

### Motivation

<br><br>
- deeper understanding of network communication, related protocols etc.
- learn C by building something
- go low level to better understand higher languages
<br><br>

---

@title[OSI Model]

### OSI Model

<br><br>
- Application Layer
- Presentation Layer
- Session Layer
- **Transport Layer**
- Network Layer
- Data Link
- Physical Layer
<br><br>

<!-- ![OSI Model](https://github.com/gitlines/bac/blob/master/img/osi.jpg) -->

---

@title[Transport Layer]

### Transport Layer

<br><br>
- provides flow control and error handling, and participates in solving problems TCP, UDP
- TCP = Transmission Control Protocol 
- makes sure data are sent and received in the correct sequence
- HTTP servers use TCP in order to provide reliable transport
<br><br>

---

@title[Sockets]

### Sockets

<br><br>
- aka Berkeley sockets:a Unix API for Internet sockets and Unix domain sockets used for inter-process communication
- mechanism used by operating systems to provide network access to programs
- network agnostic
<br><br>


---?include=template/md/code-presenting/PITCHME.md


### Challenges

@title[Challenges 1]

- starting from basically zero ... tooling, and external libraries 
- OCD: declaring pointers; asterisk on the left or right?
- double pointers? WTF

---

### Challenges

fa[arrow-down text-black]

@title[Challenges 2]


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

@title[Challenges 3]

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

