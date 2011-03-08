#ifndef TEXTSERVER_H
#define TEXTSERVER_H

#include <QObject>
#include "socket.h"
#include "component.h"

struct ClientConnect {
    ClientConnect() :data(0) {}
    int data;
};

class TextServer : public Component {
    Q_OBJECT

public:
    TextServer(int port, int bufsize);
    ~TextServer();
    virtual void Start();
public slots:
    void slotClientConnect(char * str);
    void slotClientDisconnect(char * str);
signals:
    void signalClientConnected(ClientConnect *);

private:
    Socket * pSocket;
};

#endif // TEXTSERVER
