#ifndef TEXTCLIENT_H
#define TEXTCLIENT_H

#include <QObject>
#include "socket.h"
#include "component.h"

/*
struct MesgSpecs {
    MesgSpecs():sender(0), data(0){}
    const char *sender;
    const char *data;
};
*/

class TextClient : public Component {
    Q_OBJECT

public:
    TextClient(char*, char*, int, int) ;
    ~TextClient();
    void txMessage(const QString);
    SocketClass* getSocket();

public slots:
    virtual void Start();

signals:
    void signalTextRecieved(MessageStruct *);
    void signalServerClosed();

private:
    char *ip_;
    char *alias_;
    SocketClass *pSocket_;
};

#endif // TEXTCLIENT
