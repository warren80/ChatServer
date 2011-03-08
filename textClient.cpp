#include "textClient.h"
#include <QDebug>

#define BUFSIZE 1024

TextClient::TextClient(char* ip, int port) {
    char * str = new char[BUFSIZE];
    pSocket = new Socket(1, port, BUFSIZE);
    //pSocket->rx(str);
}

void TextClient::Start() {
   // pSocket->SetAsClient(ip);
}

TextClient::~TextClient() {
}

void TextClient::slotTextRecieved(char *) {

}


