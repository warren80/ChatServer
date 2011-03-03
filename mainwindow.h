#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "textClient.h"
#include "textServer.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void printF(const char*);
    void printF(QString);

private:
    Ui::MainWindow *ui;
    QThread * textClient;
    QThread * textServer;

public slots:
    void slotClientConnected(ClientConnect *);
    void slotTextRecieved(TextReceived *);

private slots:
    void on_actionExit_triggered();
    void sendMessage();
};

#endif // MAINWINDOW_H
