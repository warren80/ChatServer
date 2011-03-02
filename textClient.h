#ifndef TEXTCLIENT_H
#define TEXTCLIENT_H

#include <QObject>

class TextClient : public QObject {
    Q_OBJECT

public:
    explicit TextClient();
    ~TextClient();

private:
};

#endif // TEXTCLIENT
