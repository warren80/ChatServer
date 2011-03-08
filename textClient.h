#ifndef TEXTCLIENT_H
#define TEXTCLIENT_H

#include <QObject>
#include "includes.h"
#include "socket.h"
#include "component.h"

struct TextReceived {
    TextReceived() :data(0) {}
    int data;
};

class TextClient : public Component {
    Q_OBJECT

public:
    TextClient(const char* ip, int port, int bufsize) ;
    ~TextClient();
    virtual void Start();
    void txMessage(const char * str);
public slots:
    void slotTextRecieved(char *);
signals:
    void signalTextRecieved(TextReceived *);
private:
    char * ip_;
    Socket * pSocket;
};

#endif // TEXTCLIENT
