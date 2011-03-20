#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

/**
 * The dialog box that will prompt the user for the application settings.
 */

typedef struct ConnSettings {
    ConnSettings():ipAddr("255.255.255.255"), alias("Local"), port(0), isClient(false){}
    QString ipAddr;
    QString alias;
    int port;
    bool isClient;
    bool logChat;
} SETTINGS, *PSETTINGS;

namespace Ui {
    class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    /**
     * The settings dialog box constructor where some variables are initialized. Some
     * connections are also done here.
     *
     * @author Karl Castillo
     * @arg parent - parent widget that owns this window
     */
    explicit Settings(QWidget *parent = 0);
    /**
     * The destructor of the settings dialog box class where objects are deleted.
     *
     * @author Karl Castillo
     */
    ~Settings();
    /**
     * A getter that will return the settings provided by the user.
     *
     * @author Karl Castillo
     * @return the settings provided by the user
     */
    PSETTINGS getSettings();

private:
    /**
    * The ui form of the settings dialog box.
    */
    Ui::Settings *ui;
    /**
     * The settings structure that holds the settings provided by the user.
     */
    PSETTINGS settings;

private slots:
    /**
     * This is called when the user accepts the settings. The setting parameters
     * will be stored into the struct.
     *
     * @author Karl Castillo
     */
    void storeSettings();
    /**
     * This is called when the user either chooses the application to be server
     * or client.
     *
     * @author client - true, if the user chooses the application to be client
     *                  false, if the user chooses the application to be server
     */
    void enableDisableClient(bool client);
};

#endif // SETTINGS_H
