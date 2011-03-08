#ifndef TEXTCLIENT_H
#define TEXTCLIENT_H

#include <QObject>
#include "socket.h"

struct TextReceived {
    TextReceived() :data(0) {}
    int data;
};

class TextClient : public QObject {
    Q_OBJECT

public:
    explicit TextClient(char* ip, int port);
    ~TextClient();
    void Start();
public slots:
    void slotTextRecieved(char *);
signals:
    void signalTextRecieved(TextReceived *);
private:
    Socket * pSocket;
};

#endif // TEXTCLIENT
