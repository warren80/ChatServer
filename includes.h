#ifndef INCLUDES_H
#define INCLUDES_H

typedef struct ConnSettings {
    ConnSettings():ipAddr("255.255.255.255"), alias("Local"), port(0), isClient(false){}
    QString ipAddr;
    QString alias;
    int port;
    bool isClient;
} SETTINGS, *PSETTINGS;

#endif // INCLUDES_H
