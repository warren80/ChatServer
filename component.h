#ifndef COMPONENT_H
#define COMPONENT_H

#include <QObject>

class Component : public QObject
{
    Q_OBJECT
public:
    Component(int port, int bufSize);
    virtual void Start() = 0;

protected:
    int bufSize_;
    int port_;

signals:
    void connectionError(const char*);
    void success(const char*);

};

#endif // COMPONENT_H
