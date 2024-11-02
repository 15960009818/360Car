// settingcontroller.h
#ifndef SETTINGCONTROLLER_H
#define SETTINGCONTROLLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
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
    void verifyNetworkConnection(const QString &ip, int port);

signals:
    void networkConnectionResult(bool success, const QString &message);

private slots:
    void onNetworkReplyFinished(QNetworkReply *reply);

private:
    SettingService *service;
    QNetworkAccessManager *networkManager;
};

#endif // SETTINGCONTROLLER_H
