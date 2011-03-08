#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "textClient.h"
#include "textServer.h"
#include "settings.h"
#include "thread.h"

#define BUFSIZE 1024

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
    void enableChat(bool);

private:
    Ui::MainWindow *ui;
    Thread * textClient;
    Thread * textServer;
    PSETTINGS settings;

public slots:
    void slotClientConnected(ClientConnect *);
    void slotTextRecieved(TextReceived *);

private slots:
    void on_actionConnect_triggered();
    void on_actionExit_triggered();
    void sendMessage();

signals:
    void startSignalClient();
    void startSignalServer();
};

#endif // MAINWINDOW_H
