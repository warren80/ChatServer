#include "textClient.h"
#include <QDebug>

TextClient::TextClient() {
    char * str = new char[3];
    Socket *s = new Socket(TCP, 7503, 3);
    s->SetAsClient("192.168.0.13");
    qDebug ("%d", s->tx(QString("moo")));
    s->rx(str);
    qDebug("%3s", str);
}

TextClient::~TextClient() {
}
