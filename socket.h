#ifndef SOCKET_H
#define SOCKET_H

#include <stdio.h>
#include <QDebug>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

class Socket
{
public:
    Socket(int type, int port);
    int bindToPort(const char * str);
    int socketDescriptor;
private:
    void createTCPSocket();
    void createUDPSocket();
};

#endif // SOCKET_H
