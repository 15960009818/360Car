#ifndef SETTINGCONTROLLER_H
#define SETTINGCONTROLLER_H

#include <QObject>
#include "../service/settingservice.h"

class SettingController : public QObject
{
    Q_OBJECT

public:
    explicit SettingController(QObject *parent = nullptr);
    ~SettingController();

    QString getIpAddress() const;
    void setIpAddress(const QString &ip);

    int getPort() const;
    void setPort(int port);

    int getStorageSize() const;
    void setStorageSize(int size);

    void loadSettings();
    void saveSettings();

private:
    SettingService *service;
};

#endif // SETTINGCONTROLLER_H
