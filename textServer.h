#ifndef TEXTSERVER_H
#define TEXTSERVER_H

#include <QObject>
#include "socket.h"

struct ClientConnect {
    ClientConnect() :data(0) {}
    int data;
};

class TextServer : public QObject {
    Q_OBJECT

public:
    explicit TextServer(int port);
    ~TextServer();
    void Start();
public slots:
    void slotClientConnect(char *);
    void slotClientDisconnect(char *);
signals:
    void signalClientConnected(ClientConnect *);

private:
    Socket * pSocket;
};

#endif // TEXTSERVER
