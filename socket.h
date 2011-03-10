#ifndef SOCKET_H
#define SOCKET_H

#include <QString>

#include <stdio.h>
#include <QDebug>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <QtGui>
#include <QFile>

#define TCP 1
#define UDP 2

#define BUFSIZE     1024
#define IPADDRSIZE  16
#define ALIASSIZE   32

struct MessageStruct {
    int mesgType; //0 text, 1 voice, 2 stream, 3 file
    char ipAddr[16];
    char alias[32];
    char data[BUFSIZE - IPADDRSIZE - ALIASSIZE];
};

class SocketClass : public QObject {
    Q_OBJECT
public:
    SocketClass(int, int);
    int SetAsClient(const char*);
    int SetAsServer();

    int tx(MessageStruct *, int);
    int tx(MessageStruct *);
    int tx(MessageStruct *, int, int);
    int rx(MessageStruct *);
    void closeSocket();
private:
    void createTCPSocket();
    void createUDPSocket();
    int TCPServer();
    int UDPServer();
    int SetupSocket(const char*);
    void writeToEveryoneElse(int maxi, int client[FD_SETSIZE],
             int recieveSocketDescriptor, MessageStruct * mesg);

    int buflen_;
    int socketType_;
    int sPort_;
    struct sockaddr_in client_, server_;
    int serverLength_;
    int socketDescriptor_;

};

#endif
