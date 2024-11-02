// settingcontroller.cpp
#include "settingcontroller.h"
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>

SettingController::SettingController(QObject *parent)
    : QObject(parent),
      service(new SettingService),
      networkManager(new QNetworkAccessManager(this)) // 初始化 networkManager
{
    connect(networkManager, &QNetworkAccessManager::finished,
            this, &SettingController::onNetworkReplyFinished);
    loadSettings();
}

SettingController::~SettingController()
{
    delete service;
}

QString SettingController::getIpAddress() const { return service->getIpAddress(); }

void SettingController::setIpAddress(const QString &ip) { service->setIpAddress(ip); }

int SettingController::getPort() const { return service->getPort(); }

void SettingController::setPort(int port) { service->setPort(port); }

int SettingController::getStorageSize() const { return service->getStorageSize(); }

void SettingController::setStorageSize(int size) { service->setStorageSize(size); }

void SettingController::loadSettings() { service->loadSettings(); }

void SettingController::saveSettings() { service->saveSettings(); }

void SettingController::verifyNetworkConnection(const QString &ip, int port) {
    QUrl url(QString("http://%1:%2").arg(ip).arg(port));
    QNetworkRequest request(url);
    networkManager->get(request);
}

void SettingController::onNetworkReplyFinished(QNetworkReply *reply) {
    if (reply->error() == QNetworkReply::NoError) {
        emit networkConnectionResult(true, "连接成功！");
    } else {
        emit networkConnectionResult(false, "无法连接到服务器，请检查网络设置。");
    }
    reply->deleteLater();
}
