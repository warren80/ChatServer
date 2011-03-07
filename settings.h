#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

typedef struct ConnSettings {
    ConnSettings():ipAddr("255.255.255.255"), alias("Local"), port(0), isClient(false){}
    QString ipAddr;
    QString alias;
    int port;
    bool isClient;
} SETTINGS, *PSETTINGS;

namespace Ui {
    class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();
    PSETTINGS getSettings();

private:
    Ui::Settings *ui;
    PSETTINGS settings;

private slots:
    void storeSettings();
    void enableDisableClient(bool);
};

#endif // SETTINGS_H
