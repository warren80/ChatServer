#include "socket.h"

Socket::Socket(int type, int port, int packetSize)
{
    sPort_ = port;
    socketType_ = type;
    buflen_ = packetSize;
    switch (socketType_) {
    case TCP:
        createTCPSocket();
        break;
    case UDP:
        createUDPSocket();
        break;
    default:
        qDebug("Socket(): invalid socket type");
        return;
    }
}

int Socket::SetAsClient(const char * str) {
    struct hostent *hp;

    if (str == 0) {
        qDebug("SetAsClient(): null str error");
        return -1;
    }
    server_.sin_family = AF_INET;
    server_.sin_port = htons(sPort_);

    if ((hp = gethostbyname(str)) == NULL) {
        qDebug("SetAsClient(): getHostByName");
        return -1;
    }
    bcopy(hp->h_addr, (char *) &server_.sin_addr, hp->h_length);

    client_.sin_family = AF_INET;
    client_.sin_port = htons(0);
    client_.sin_addr.s_addr = htonl(INADDR_ANY);

    switch(socketType_) {
    case UDP:
        if (bind(socketDescriptor_, (struct sockaddr *)&client_ , sizeof(client_)) == -1) {
            qDebug("SetAsClient(): failure to bind to port");
            return -1;
        }
        break;
    case TCP:
        if (connect(socketDescriptor_, (struct sockaddr *) &server_, sizeof(server_)) == -1) {
            qDebug("SetAsClient(): failure to connect to port");
            return -1;
        }
        break;
    }

    return 1;
}

void Socket::createTCPSocket() {
    int arg = 1;
    if ((socketDescriptor_ = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            qDebug("createTCPSocket(): Cannot Create Socket");
    }
    if (setsockopt (socketDescriptor_, SOL_SOCKET, SO_REUSEADDR, &arg, sizeof(arg)) == -1) {
            qDebug("createTCPSocket(): setsockopt");
    }
    return;
}

void Socket::createUDPSocket() {
    int arg = 1;
    if ((socketDescriptor_ = socket(AF_INET, SOCK_DGRAM, 0)) == -1)  {
        qDebug("createUDPSocket(): Cannot Create Socket!");
    }
    if (setsockopt (socketDescriptor_, SOL_SOCKET, SO_REUSEADDR, &arg, sizeof(arg)) == -1) {
        qDebug("createUDPSocket(): setsockopt");
    }
}

int Socket::tx(const char * str, int length) {
    switch (socketType_) {
    case TCP:
        return send(socketDescriptor_, str, length, 0);
    case UDP:
        return sendto(socketDescriptor_, str, length, 0, (struct sockaddr *) &server_, serverLength_);
    default:
        qDebug("Socket(): invalid socket type");
        return -1;
    }
}

int Socket::tx(const QString str) {
    return tx(str.toLatin1(), str.length());
}

int Socket::rx(char * str) {
    int n = 0;
    int bytesToRead = buflen_;

    while((n !=  buflen_)) {
        switch (socketType_) {
        case TCP:
            n = recv(socketDescriptor_, str, bytesToRead, 0);
            break;
        case UDP:
            //n = recvfrom(socketDescriptor_, str, bytesToRead, 0, (struct sockaddr *) &server_, sizeof(server_));
            break;
        default:
            qDebug("Socket(): invalid socket type");
            return -1;
        }
        bytesToRead -= n;
        str += n;
    }
    return n;
}
