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

#define TCP 1
#define UDP 2



typedef struct MessageStruct {
    int mesgType; //0 text, 1 voice, 2 stream, 3 file
    char ipAddr[16];
    char alias[32];
    char data[1024]; //1072
} MESSAGESTRUCT, *PMESSAGESTRUCT;
Q_DECLARE_METATYPE(MessageStruct);


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
