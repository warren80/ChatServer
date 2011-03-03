#ifndef TEXTSERVER_H
#define TEXTSERVER_H

#include <QObject>

struct ClientConnect {
    ClientConnect() :data(0) {}
    int data;
};

class TextServer : public QObject {
    Q_OBJECT

public:
    explicit TextServer(int port);
    ~TextServer();
public slots:
signals:
    void signalClientConnected(ClientConnect *);

private:
};

#endif // TEXTSERVER
