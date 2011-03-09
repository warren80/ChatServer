#ifndef TEXTCLIENT_H
#define TEXTCLIENT_H

#include <QObject>
#include "socket.h"
#include "component.h"

typedef struct MesgSpecs {
    MesgSpecs():sender(0), data(0){}
    const char *sender;
    const char *data;
}MESGSPECS, *PMESGSPECS;

class TextClient : public Component {
    Q_OBJECT

public:
    TextClient(char*, char*, int, int) ;
    ~TextClient();
public slots:
    virtual void Start();
    void txMessage(const QString);
signals:
    void signalTextRecieved(PMESGSPECS);
private:
    char *ip_;
    char *alias_;
    SocketClass *pSocket_;
};

#endif // TEXTCLIENT
