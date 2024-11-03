#include "settingcontroller.h"

SettingController::SettingController(QObject *parent)
    : QObject(parent), service(new SettingService)
{
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
