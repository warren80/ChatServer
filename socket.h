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

#define TCP 1
#define UDP 2

typedef struct MessageStruct {
    MessageStruct():mesgType(-1), ipAddr(0), alias(0), data(0), mesgLen(0){}
    int mesgType; //0 text, 1 voice, 2 stream, 3 file
    char *ipAddr;
    char *alias;
    char *data;
    int mesgLen;
} MESSAGESTRUCT, *PMESSAGESTRUCT;

class SocketClass : public QObject {
    Q_OBJECT
public:
    SocketClass(int, int, int);
    int SetAsClient(const char*);
    int SetAsServer();

    int tx(PMESSAGESTRUCT, int);
    int tx(PMESSAGESTRUCT);
    int tx(PMESSAGESTRUCT, int, int);
    int rx(PMESSAGESTRUCT);
    void closeSocket();
private:
    void createTCPSocket();
    void createUDPSocket();
    int TCPServer();
    int UDPServer();
    int SetupSocket(const char*);

    int buflen_;
    int socketType_;
    int sPort_;
    struct sockaddr_in client_, server_;
    int serverLength_;
    int socketDescriptor_;

signals:
    void SignalClientConnected(char*);
    void SignalClientDisconnected(char*);

};

#endif
