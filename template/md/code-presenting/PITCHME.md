## Code

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

@[51-22](implementing HTTP - needs 3 Headers; *HTTP/1.1 200 OK*, *Content-Type: text/plain*, *Content-Length: 12*)

@[54-59](original socket for listening is only for accepting connections, not for exchanging data)

@[51, 60-71]




