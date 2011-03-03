#include "socket.h"

#define TCP 1
#define UDP 2

/*

int buflen;

int i, maxi, nready, bytes_to_read, arg;
int listen_sd, new_sd, sockfd, client_len, port, maxfd, client[FD_SETSIZE];
struct sockaddr_in server, client_addr;
char *bp, buf[buflen];
ssize_t n;
fd_set rset, allset;

Socket::Socket(int type, int port)
{
    initSocket(tcp); //creates socket

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = htonl(INADDR_ANY); // Accept connections from any client

    if (bind(listen_sd, (struct sockaddr *)&server, sizeof(server)) == -1)
        SystemFatal("bind error");
}
//public
void Socket::setSocketType() {
    switch
}


int Socket::createTCPSocket() {
    int s;
    struct sockaddr_in server;
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            qDebug("createTCPSocket(): Cannot Create Socket!");
    }
    if (setsockopt (listen_sd, SOL_SOCKET, SO_REUSEADDR, &arg, sizeof(arg)) == -1) {
            qDebug("createTCPSocket(): setsockopt");
    }


    return s;
}

int Socket::createUDPSocket() {
    int s;
    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == -1)  {
        qDebug("createUDPSocket(): Cannot Create Socket!");
    }
    if (setsockopt (listen_sd, SOL_SOCKET, SO_REUSEADDR, &arg, sizeof(arg)) == -1) {
        qDebug("createUDPSocket(): setsockopt");
    }
    return s;
}
*/
