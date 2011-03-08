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

int Socket::SetAsServer() {
    if (socketType_ == UDP) {
        qDebug("SetAsServer(): UDP server not created");
        return -1;
    }
    if (SetupSocket(0) != 1) {
        qDebug("SetAsServer(): SetupSocket");
        return -1;
    }
    return TCPServer();
}

int Socket::TCPServer() {
    int maxfd, maxi, nready, bytesToRead, n, i;
    socklen_t clientLength;
    int client[FD_SETSIZE];
    int newSocketDescriptor, recieveSocketDescriptor;
    struct sockaddr_in clientAddr;
    fd_set allset, rset;
    char * bp, buffer[buflen_];


    if(bind(socketDescriptor_, (struct sockaddr *) &server_, sizeof(server_)) == -1) {
        qDebug("TCPServer(): bind");
        return -1;
    }
    listen(socketDescriptor_, FD_SETSIZE);
    maxfd = socketDescriptor_;
    maxi = -1;

    for (i = 0; i < FD_SETSIZE; i++) {
        client[i] = -1;
        Socket(TCP, sPort_, buflen_);
    }

    FD_ZERO(&allset);
    FD_SET(socketDescriptor_, &allset);

    while (1) {
        rset = allset;
        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if (FD_ISSET(socketDescriptor_, &rset)) {
            clientLength = sizeof(clientAddr);
            if ((newSocketDescriptor = accept(socketDescriptor_, (struct sockaddr *) &clientAddr, &clientLength)) == -1) {
                qDebug("TCPServer(): accept");
                return -1;
            }
            //some sort of emit here inet_ntoa(clientAddr.sin_addr);
            for (i = 0; i < FD_SETSIZE; ++i) {
                if (client[i] != 0) {
                    client[i] = newSocketDescriptor;
                    break;
                }
            }
            if (i == FD_SETSIZE) {
                qDebug("TCPServer(): Too many connections");
                return -1;
            }
            FD_SET(newSocketDescriptor, &allset);
            if (newSocketDescriptor > maxfd) {
                maxfd = newSocketDescriptor;
            }
            if (i > maxi) {
                maxi = i;
            }
            if (--nready <= 0) {
                continue;
            }
        } //end add new socket
        //start check for new data
        for (i = 0; i <= maxi; i++) {
            if ((recieveSocketDescriptor = client[i]) < 0) {
                continue;
            }
            if (FD_ISSET (recieveSocketDescriptor,&rset)) {
                bp = buffer;
                bytesToRead = buflen_;
                while((n = recv(recieveSocketDescriptor, bp, bytesToRead, NULL)) > 0) {
                    bp += n;
                    bytesToRead -= n;
                }
                //emit data to server probably have to copy this info for use in another thread

                //write loop to all clients but this one
                for(int j = 0; j < maxi; j++) {
                    if(client[i] != -1) {
                        tx(buffer, buflen_, client[i]);
                    }
                }

                if (n == 0) //connection closed by client
                {
                    // emit signal that inet_ntoa(clientAddr.sin_addr)) has been closed
                    close(recieveSocketDescriptor);
                    FD_CLR(recieveSocketDescriptor, &allset);
                    client[i] = -1;
                }
                if (--nready <= 0) {
                    break;
                }
            } //end of FD_ISSET
        } //end of read/write loop
    } //end of while loop
}

int Socket::UDPServer() {
    return 1;
}

int Socket::SetupSocket(const char * str) {
    struct hostent *hp;

    server_.sin_family = AF_INET;
    server_.sin_port = htons(sPort_);
    if (str != 0) {
        if ((hp = gethostbyname(str)) == NULL) {
            qDebug("SetupSocket(): getHostByName(): No such server available.");
            return -1;
        }
        bcopy(hp->h_addr, (char *) &server_.sin_addr, hp->h_length);
    } else {
        server_.sin_addr.s_addr = htonl(INADDR_ANY);
        return 1;
    }
    client_.sin_family = AF_INET;
    client_.sin_port = htons(sPort_);

    return 1;
}

int Socket::SetAsClient(const char * str) {
    if (SetupSocket(str) == -1) {
        return -1;
    }
    switch(socketType_) {
    case UDP:
        if (bind(socketDescriptor_, (struct sockaddr *)&client_ , sizeof(client_)) == -1) {
            qDebug("SetAsClient(): failure to bind to port");
            return -1;
        }
        break;
    case TCP:
        if (::connect(socketDescriptor_, (struct sockaddr *) &server_, sizeof(server_)) == -1) {
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
    return tx(str.toLatin1().data(), str.length());
}

int Socket::tx(const char *str, int length, int socketDescriptor) {
    switch (socketType_) {
    case TCP:
        return send(socketDescriptor, str, length, 0);
    case UDP:
        return sendto(socketDescriptor, str, length, 0, (struct sockaddr *) &server_, serverLength_);
    default:
        qDebug("Socket(): invalid socket type");
        return -1;
    }
}

int Socket::rx(char * str) {
    int n = 0;
    int bytesToRead = buflen_;

    while((n !=  buflen_)) {
        switch (socketType_) {
        case TCP:
            n = recv(socketDescriptor_, str, bytesToRead, 0);
            if (n == -1) {
                qDebug ("Rx(): recv(): error");
                return -1;
            }
            if (n == 0) {
                return 0;
            }
            break;
        case UDP:
            //n = recvfrom(socketDescriptor_, str, bytesToRead, 0, (struct sockaddr *) &server_, sizeof(server_));
            break;
        default:
            qDebug("Rx(): invalid socket type");
            return -1;
        }
        bytesToRead -= n;
        str += n;
    }
    return n;
}

void Socket::closeSocket() {
    close(socketDescriptor_);
}
