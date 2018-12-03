# Code

@fa[arrow-down text-black]


+++?code=template/src/c/main.c&lang=c
@title[Source File]

@[1-21]

@[15-23](declaring .... also: **server_fd** is a file descriptor)

@[21](enables OS read bytes that identify the address family corresponds to socket that is set up)

@[24-28](create socket fd via system call)(**domain:** AF_INET (IP), AF_INET6 (IPv6), AF_UNIX)(**type:** SOCK_STREAM (=TCP), SOCK_DGRAM (=UDP))(**protocol:** not 0 only when IP address family has variations)

@[30-38](configure socket addr struct in in correspondence with socket settings)






