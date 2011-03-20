#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "textClient.h"
#include "textServer.h"
#include "settings.h"
#include "thread.h"

namespace Ui {
    class MainWindow;
}

/**
 * The main window class. This where the GUI is located. This is also where
 * the user will be informed about errors and other important information about
 * the session.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * The main window constructor where some variables are initialized. Some
     * connections are also done here.
     *
     * @author Karl Castillo, Warren Voelkl
     * @arg parent - parent widget that owns this window
     */
    explicit MainWindow(QWidget *parent = 0);
    /**
     * The destructor of the main window class where objects are deleted.
     *
     * @author Karl Castillo
     */
    ~MainWindow();
    /**
     * A wrapper function that will be used to print out information, or messages
     * on to the chat screen.
     *
     * @author Karl Castillo
     * @arg message - the message to be printed on to the screen
     */
    void printF(const char *message);
    /**
     * An overloaded printF function that takes in a QString instead of a const
     * char*
     *
     * @author Karl Castillo
     * @arg message - the message to be printed on to the screen
     */
    void printF(QString message);
    /**
     * Enables or disables the type screen and send button.
     *
     * @author Karl Castillo
     * @arg enable - true, if it should be enabled
     *               false, if it should be disabled
     */
    void enableChat(bool enable);
    /**
     * Function that will save the chat into a file.
     *
     * @author Karl Castillo
     */
    void saveChat();

protected:
    /**
     * This method is called when the main window is closed. It will save the
     * chat if the user stated that he/she wanted it to be saved.
     *
     * @author Karl Castillo
     */
    void closeEvent(QCloseEvent *);

private:
    /**
     * The ui form of the main window.
     */
    Ui::MainWindow *ui;
    /**
     * The thread that will hold the client session.
     */
    Thread * textClient;
    /**
     * The thread that will hold the server session.
     */
    Thread * textServer;
    /**
     * The struct that will hold the settings specified by the user from the
     * settings dialog box.
     */
    PSETTINGS settings;
    /**
     * Used if the user chose the application to be the client.
     */
    TextClient *tc_;
    /**
     * Used if the use chose the application to be the server.
     */
    TextServer *ts_;
    /**
     * A boolean that will determine whether the application is connected or not.
     */
    bool connected_;

public slots:
    /**
     * This is called when the client receives that message from another user.
     *
     * @author Karl Castillo, Warren Voelkl
     */
    void slotTextRecieved(MessageStruct *);
    /**
     * This is called when a client connects to the server. The ip address will
     * be printed out on to the screen.
     *
     * @author Karl Castillo
     */
    void slotClientActivity(QString);

private slots:
    /**
     * This is called when the user chose the disconnect menu item. Closes the
     * socket.
     *
     * @author Karl Castillo
     */
    void on_actionDisconnect_triggered();
    /**
     * This is called when the user chose the connect menu item. Connects to the
     * server or listens for clients.
     *
     * @author Karl Castillo
     */
    void on_actionConnect_triggered();
    /**
     * This is called when the user chose the exit menu item. Closes the window.
     *
     * @author Karl Castillo
     */
    void on_actionExit_triggered();
    /**
     * This is called when the user presses the "send" button.
     *
     * @author Karl Castillo
     */
    void sendMessage();
    /**
     * This is called when an error occurs while connecting or creating a socket.
     *
     * @author Karl Castillo
     * @arg error - the error message.
     */
    void error(const char *error);
    /**
     * This is called when the application successfully created a socket descriptor.
     *
     * @author Karl Castillo
     * @arg message - the success message.
     */
    void success(const char *message);
    /**
     * This is called when the server closed for any reason.
     *
     * @author Karl Castillo
     */
    void slotServerClosed();

signals:
    /**
     * Emitted to start the client session.
     */
    void startSignalClient();
    /**
     * Emitted to start the server session.
     */
    void startSignalServer();
};

#endif // MAINWINDOW_H
