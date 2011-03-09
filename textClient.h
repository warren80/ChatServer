#ifndef TEXTCLIENT_H
#define TEXTCLIENT_H

#include <QObject>
#include "socket.h"
#include "component.h"

struct TextReceived {
    TextReceived() :data(0) {}
    QString alias;
    int data;
};

class TextClient : public Component {
    Q_OBJECT

public:
    TextClient(const char*, int, int) ;
    ~TextClient();
public slots:
    void slotTextRecieved(char*);
    virtual void Start();
    void txMessage(const QString);
signals:
    void signalTextRecieved(TextReceived*);
private:
    char * ip_;
    SocketClass *pSocket_;
};

#endif // TEXTCLIENT
