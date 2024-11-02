#ifndef SETTINGSERVICE_H
#define SETTINGSERVICE_H

#include <QString>
#include <QSettings>
#include <qobject.h>
class SettingService: public QObject
{
    Q_OBJECT
public:
    SettingService(const QString &configPath = "../SettingConfig.ini");
    ~SettingService();

    QString getIpAddress() const;
    void setIpAddress(const QString &ip);

    int getPort() const;
    void setPort(int port);

    int getStorageSize() const;
    void setStorageSize(int size);

    void loadSettings();
    void saveSettings();

private:
    QString configPath;
    QString ipAddress;
    int port;
    int storageSize;

    QSettings *settings;
};

#endif // SETTINGSERVICE_H
