#include "socket.h"

#define TCP 1
#define UDP 2
#define LISTEN 3



int buflen;
int socketType;
int sPort;
struct sockaddr_in socketAddr;

//int i, maxi, nready, bytes_to_read, arg;
//int new_sd, sockfd, client_len, port, maxfd;// client[FD_SETSIZE];
//char *bp, buf[buflen];
//ssize_t n;
//fd_set rset, allset;

Socket::Socket(int type, int port)
{
    sPort = port;
    socketType = type;
    switch (socketType) {
    case TCP:
        break;
    case UDP:
        break;
    default:
        qDebug("Socket(): invalid socket type");
        return;
    }
    //if (bind(listen_sd, (struct sockaddr *)&server, sizeof(server)) == -1)
    //    SystemFatal("bind error");
}


//public
int Socket::bindToPort(const char * str) {
    struct hostent *hp;

    if (str == 0) {
        qDebug("setSocketType(): null str error");
        return -1;
    }
    socketAddr.sin_family = AF_INET;
    socketAddr.sin_port = htons(sPort);
    if (strlen(str) == 1 && str[0] == LISTEN) {
        socketAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    } else {
       hp = gethostbyname(str);
       if (hp == 0) {
           qDebug("setSocketType(): invalid hostname");
           return -1;
       }
       bcopy(hp->h_addr, (char *) &socketAddr.sin_addr, hp->h_length);
    }
    if (bind(socketDescriptor, (struct sockaddr *)&socketAddr , sizeof(socketAddr)) == -1) {
        qDebug("bindToPort(): failure to bind to port");
        return -1;
    }
    return 1;
}

void Socket::createTCPSocket() {
    int arg = 1;
    struct sockaddr_in server;
    if ((socketDescriptor = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            qDebug("createTCPSocket(): Cannot Create Socket");
    }
    if (setsockopt (socketDescriptor, SOL_SOCKET, SO_REUSEADDR, &arg, sizeof(arg)) == -1) {
            qDebug("createTCPSocket(): setsockopt");
    }
    return;
}

void Socket::createUDPSocket() {
    int arg = 1;
    if ((socketDescriptor = socket(AF_INET, SOCK_DGRAM, 0)) == -1)  {
        qDebug("createUDPSocket(): Cannot Create Socket!");
    }
    if (setsockopt (socketDescriptor, SOL_SOCKET, SO_REUSEADDR, &arg, sizeof(arg)) == -1) {
        qDebug("createUDPSocket(): setsockopt");
    }
}

int Socket::write(const char * str, int length) {
    switch (socketType) {
    case TCP:
        send(socketDescriptor, str, length, 0);
    case UDP:
        return sendto(socketDescriptor, str, length, 0, (struct sockaddr *) socketAddr, sizeof(socketAddr));
    default:
        qDebug("Socket(): invalid socket type");
        return;
    }
}

int Socket::write(QString str) {
    write(str.toLatin1(), str.length());
}
