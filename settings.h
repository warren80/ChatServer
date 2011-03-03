#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

typedef struct {
    QString ipAddr;
    int port;
    bool isClient;
    bool accepted;
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
    void cancelSettings();
    void enableDisableClient(bool);
};

#endif // SETTINGS_H
