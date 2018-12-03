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


---

### Challenges

- starting from basically zero ... tooling, and external libraries 
- OCD: declaring pointers; asterisk on the left or right?
- double pointers? WTF

@fa[arrow-down text-black]

@title[Challenges]

+++?code=template/src/c/main-improved.c&lang=c




@[1-15]

@[1-15]



@title[Pointer to Pointers]








