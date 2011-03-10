#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "textClient.h"
#include "textServer.h"
#include "settings.h"
#include "thread.h"

#define BUFSIZE 1072

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
    TextClient *tc_;

public slots:
    void slotClientConnected(PCLIENTSPECS);
    void slotTextRecieved(PMESGSPECS);

private slots:
    void on_actionConnect_triggered();
    void on_actionExit_triggered();
    void sendMessage();
    void error(const char*);
    void success(const char*);

signals:
    void startSignalClient();
    void startSignalServer();
    void sendMessage(const QString);
};

#endif // MAINWINDOW_H
