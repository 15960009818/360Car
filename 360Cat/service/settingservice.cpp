#include "settingservice.h"
#include <QFile>

SettingService::SettingService(const QString &configPath)
    : configPath(configPath), settings(new QSettings(configPath, QSettings::IniFormat))
{
    loadSettings();
}

SettingService::~SettingService()
{
    delete settings;
}

QString SettingService::getIpAddress() const { return ipAddress; }

void SettingService::setIpAddress(const QString &ip) { ipAddress = ip; }

int SettingService::getPort() const { return port; }

void SettingService::setPort(int port) { this->port = port; }

int SettingService::getStorageSize() const { return storageSize; }

void SettingService::setStorageSize(int size) { storageSize = size; }

void SettingService::loadSettings()
{
    ipAddress = settings->value("Server/IP", "127.0.0.1").toString();
    port = settings->value("Server/Port", 8080).toInt();
    storageSize = settings->value("Storage/Size", 5000).toInt(); // 默认大小 5000 MB
}

void SettingService::saveSettings()
{
    settings->setValue("Server/IP", ipAddress);
    settings->setValue("Server/Port", port);
    settings->setValue("Storage/Size", storageSize);
    settings->sync();
}
