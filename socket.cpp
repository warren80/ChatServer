#include "socket.h"
#include <QDateTime>
#include <errno.h>

SocketClass::SocketClass(int type, int port) {
    sPort_ = port;
    socketType_ = type;
    buflen_ = sizeof(MessageStruct);

    log_ = new QFile("log");
    errorLog_ = new QFile("errorLog");

    errorLog_->open(QIODevice::WriteOnly);

    errorLog_->write(QString("Error Log ("
                       + QDateTime::currentDateTime().toString()
                       + ")").toLatin1().data());

    errorLog_->close();

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

int SocketClass::SetAsServer() {
    if (socketType_ == UDP) {
        qDebug("SetAsServer(): UDP server not created");
        return -1;
    }
    if (SetupSocket(0) != 1) {
        qDebug("SetAsServer(): SetupSocket");
        return -1;
    }

    TCPServer();
    return 1;
}

int SocketClass::TCPServer() {
    int maxfd, maxi, nready, bytesToRead, n, i;
    socklen_t clientLength;
    int client[FD_SETSIZE];
    int newSocketDescriptor, recieveSocketDescriptor;
    struct sockaddr_in clientAddr;
    fd_set allset, rset;

    MessageStruct * tempMesg;
    MessageStruct * mesg = new MessageStruct();

    if(!log_->open(QIODevice::WriteOnly)) {
        return -1;
    }

    log_->write(QString("Server Log (Started"
                       + QDateTime::currentDateTime().toString()
                       + ")").toLatin1().data());

    log_->close();

    if(bind(socketDescriptor_, (struct sockaddr *) &server_,
            sizeof(server_)) == -1) {
        qDebug("TCPServer(): bind");
        writeToLog(errorLog_, QString("\nTCPServer(): bind - Errno(" + QString::number(errno)
                                      + " ~ " + QTime::currentTime().toString() + ")"));
        return -1;
    }

    qDebug("Listening for clients");
    listen(socketDescriptor_, FD_SETSIZE);
    maxfd = socketDescriptor_;
    maxi = -1;

    for (i = 0; i < FD_SETSIZE; i++) {
        client[i] = -1;
    }

    FD_ZERO(&allset);
    FD_SET(socketDescriptor_, &allset);

    while (1) {
        rset = allset;
        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if (FD_ISSET(socketDescriptor_, &rset)) {
            clientLength = sizeof(clientAddr);
            if ((newSocketDescriptor = accept(socketDescriptor_,
                                              (struct sockaddr *) &clientAddr,
                                              &clientLength)) == -1) {
                qDebug("TCPServer(): accept");
                writeToLog(errorLog_, QString("\nTCPServer(): accept - Errno(" + QString::number(errno)
                                              + " ~ " + QTime::currentTime().toString() + ")"));
                return -1;
            }
           qDebug("TCPServer(): connection accepted %s ",
                inet_ntoa(clientAddr.sin_addr)); //change to emit

           writeToLog(log_, QString("\nIP: "
                                    + QString(inet_ntoa(clientAddr.sin_addr))
                                    + " (Connected: " + QTime::currentTime().toString()
                                    + ")"));

            //some sort of emit here inet_ntoa(clientAddr.sin_addr);
            for (i = 0; i < FD_SETSIZE; ++i) {
                if (client[i] < 0) {
                    client[i] = newSocketDescriptor;
                    break;
                }
            }
            if (i == FD_SETSIZE) {
                qDebug("TCPServer(): Too many connections");
                writeToLog(errorLog_, QString("\nTCPServer(): Too many clients"
                                              + QTime::currentTime().toString()));
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
        //start check for new dat            emit SignalClientConnected(inet_ntoa(clientAddr.sin_addr));a
        for (i = 0; i <= maxi; i++) {
            if ((recieveSocketDescriptor = client[i]) < 0) {
                continue;
            }
            if (FD_ISSET (recieveSocketDescriptor,&rset)) {
                tempMesg = mesg;
                bytesToRead = buflen_;
                while(bytesToRead != 0 && (n = read(recieveSocketDescriptor, tempMesg, bytesToRead)) > 0) {
                    tempMesg += n;
                    bytesToRead -= n;
                }

                //emit data to server probably have to copy this info for use in another thread
                qDebug(mesg->ipAddr);
                qDebug(mesg->data);
                qDebug(QString::number(recieveSocketDescriptor).toLatin1().data());

                //write to all but current fn
                //
                writeToEveryoneElse(maxi, client, recieveSocketDescriptor, mesg);

                //write loop to all clients but this one
                if (n == 0) //connection closed by client
                {
                    writeToLog(log_, QString("\nIP: "
                                             + QString(inet_ntoa(clientAddr.sin_addr))
                                             + " (Disconnected: " + QTime::currentTime().toString()
                                             + ")"));
                    qDebug("TCPServer(): Connection disconnected %s",
                           inet_ntoa(clientAddr.sin_addr));
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

void SocketClass::writeToEveryoneElse(int maxi, int client[FD_SETSIZE], int recieveSocketDescriptor, MessageStruct * mesg) {
    for(int j = 0; j < maxi + 1; j++) {  //this loop still doesn't work right
        if(client[j] != -1 && client[j] != recieveSocketDescriptor) {
            tx(mesg, buflen_, client[j]);
        }
    }
}

int SocketClass::UDPServer() {
    return 1;
}

int SocketClass::SetupSocket(const char * str) {
    struct hostent *hp;
    bzero((char *)&server_, sizeof(struct sockaddr_in));
    server_.sin_family = AF_INET;
    server_.sin_port = htons(sPort_);
    if (str != 0) {
        if ((hp = gethostbyname(str)) == NULL) {
            qDebug("SetupSocket(): getHostByName(): No such server available.");
            writeToLog(errorLog_, QString("\nSetupSocket(): getHostByName - Errno(" + QString::number(errno)
                                          + " ~ " + QTime::currentTime().toString() + ")"));
            return -1;
        }
        bcopy(hp->h_addr, (char *)&server_.sin_addr, hp->h_length);
    } else {
        server_.sin_addr.s_addr = htonl(INADDR_ANY);
        return 1;
    }
    client_.sin_family = AF_INET;
    client_.sin_port = htons(sPort_);

    return 1;
}

int SocketClass::SetAsClient(const char * str) {
    if (SetupSocket(str) == -1) {
        return -1;
    }
    switch(socketType_) {
    case UDP:
        if (bind(socketDescriptor_, (struct sockaddr *)&client_ ,
                 sizeof(client_)) == -1) {
            qDebug("SetAsClient(): failure to bind to port");
            return -1;
        }
        break;
    case TCP:
        if (::connect(socketDescriptor_, (struct sockaddr*)&server_,
                      sizeof(server_)) == -1) {
            qDebug("SetAsClient(): failure to connect to port");
            qDebug(QString::number(errno).toLatin1().data());
            writeToLog(errorLog_, QString("\nSetAsClient(): connect - Errno(" + QString::number(errno)
                                          + " ~ " + QTime::currentTime().toString() + ")"));
            return -1;
        }
        break;
    }

    return 1;
}

void SocketClass::createTCPSocket() {
    int arg = 1;
    if ((socketDescriptor_ = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            qDebug("createTCPSocket(): Cannot Create Socket");
            writeToLog(errorLog_, QString("\ncreateTCPSocket(): socket - Errno(" + QString::number(errno)
                                          + " ~ " + QTime::currentTime().toString() + ")"));
    }
    if (setsockopt (socketDescriptor_, SOL_SOCKET, SO_REUSEADDR, &arg,
                    sizeof(arg)) == -1) {
        writeToLog(errorLog_, QString("\nTCPServer(): setsockopt - Errno(" + QString::number(errno)
                                      + " ~ " + QTime::currentTime().toString() + ")"));
        qDebug("createTCPSocket(): setsockopt");
    }
    qDebug("createTCPSocket(): Socket Created");
    return;
}

void SocketClass::createUDPSocket() {
    int arg = 1;
    if ((socketDescriptor_ = socket(AF_INET, SOCK_DGRAM, 0)) == -1)  {
        qDebug("createUDPSocket(): Cannot Create Socket!");
    }
    if (setsockopt (socketDescriptor_, SOL_SOCKET, SO_REUSEADDR, &arg,
                    sizeof(arg)) == -1) {
        qDebug("createUDPSocket(): setsockopt");
    }
}

int SocketClass::tx(MessageStruct * mesg, int length) {
    int temp;
    switch (socketType_) {
    case TCP:
        if((temp = send(socketDescriptor_, mesg, length, 0)) == -1) {
            writeToLog(errorLog_, QString("\ntx(): send - Errno(" + QString::number(errno)
                                          + " ~ " + QTime::currentTime().toString() + ")"));
        }
        return temp;
    case UDP:
        return sendto(socketDescriptor_, mesg, length, 0,
                      (struct sockaddr *) &server_, serverLength_);
    default:
        qDebug("Socket(): invalid socket type");
        return -1;
    }
}

int SocketClass::tx(MessageStruct * mesg) {
    return tx(mesg, sizeof(MessageStruct));
}

int SocketClass::tx(MessageStruct * mesg, int length, int socketDescriptor) {
    int temp;
    switch (socketType_) {
    case TCP:
        qDebug(QString::number(socketDescriptor).toLatin1().data());
        if((temp = send(socketDescriptor, mesg, length, 0)) == -1) {
            writeToLog(errorLog_, QString("\ntx(): send - Errno(" + QString::number(errno)
                                          + " ~ " + QTime::currentTime().toString() + ")"));
        }
        return -1;
    case UDP:
        return sendto(socketDescriptor, mesg, length, 0,
                      (struct sockaddr*)&server_, serverLength_);
    default:
        qDebug("Socket(): invalid socket type");
        return -1;
    }
}

int SocketClass::rx(MessageStruct * mesg) {
    int n = 0;
    int bytesToRead = buflen_;

    while((n !=  buflen_)) {
        switch (socketType_) {
        case TCP:
            n = recv(socketDescriptor_, mesg, bytesToRead, 0);
            qDebug(mesg->data);
            if (n == -1) {
                qDebug ("Rx(): recv(): error");
                writeToLog(errorLog_, QString("\nrx(): recv - Errno(" + QString::number(errno)
                                              + " ~ " + QTime::currentTime().toString() + ")"));
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
        mesg += n;
    }
    return n;
}

void SocketClass::closeSocket() {
    qDebug("Closing socket");
    close(socketDescriptor_);
}

void SocketClass::writeToLog(QFile *log, QString logMesg) {
    log->open(QIODevice::Append);
    log->write(logMesg.toLatin1().data());
    log->close();
}
