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
    TextServer(int, int);
    ~TextServer();
public slots:
    void slotClientConnect(char*);
    void slotClientDisconnect(char*);
    virtual void Start();
signals:
    void signalClientConnected(ClientConnect *);
    void connectionError(const char *);

private:
    Socket * pSocket;
};

#endif // TEXTSERVER
