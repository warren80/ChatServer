#ifndef TEXTCLIENT_H
#define TEXTCLIENT_H

#include <QObject>
#include "includes.h"
#include "socket.h"

struct TextReceived {
    TextReceived() :data(0) {}
    int data;
};

class TextClient : public QObject {
    Q_OBJECT

public:
    explicit TextClient();
    ~TextClient();
public slots:
signals:
    void signalTextRecieved(TextReceived *);
private:
};

#endif // TEXTCLIENT
