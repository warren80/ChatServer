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
Q_DECLARE_METATYPE(MESGSPECS);
Q_DECLARE_METATYPE(PMESGSPECS);

class TextClient : public Component {
    Q_OBJECT

public:
    TextClient(char*, char*, int, int) ;
    ~TextClient();
    void txMessage(const QString);
public slots:
    virtual void Start();
signals:
    void signalTextRecieved(PMESGSPECS);
private:
    char *ip_;
    char *alias_;
    SocketClass *pSocket_;
};

#endif // TEXTCLIENT
