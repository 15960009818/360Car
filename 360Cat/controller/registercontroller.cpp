#include "registercontroller.h"
#include <QCryptographicHash>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

RegisterController::RegisterController() : manager(new QNetworkAccessManager(this))
{
    connect(manager, &QNetworkAccessManager::finished, this, &RegisterController::onRegisterReplyFinished);
}

RegisterController::~RegisterController()
{
    qDebug() << "[DEBUG] RegisterController destroyed.";
}

void RegisterController::registerUser(const RegisterData &data)
{
    qDebug() << "[DEBUG] Registering user:" << data.account;

    // 检查用户输入是否为空
    if (data.account.isEmpty() || data.name.isEmpty() || data.password.isEmpty()) {
        emit finishedRegisterUISignal("用户输入不能为空。");
        return;
    }

    // MD5加密
    QString encryptedPassword = QString(QCryptographicHash::hash(data.password.toUtf8(), QCryptographicHash::Md5).toHex());
    qDebug() << "[DEBUG] Encrypted password (MD5):" << encryptedPassword;

    // 设置URL
    QUrl url("https://XiangJun.666/register"); // 注册的URL
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json;
    json["account"] = data.account; // 用户账号
    json["name"] = data.name; // 用户昵称
    json["password"] = encryptedPassword; // 加密后的密码

    QJsonDocument jsonDoc(json);
    QByteArray jsonData = jsonDoc.toJson();
    qDebug() << "[DEBUG] JSON data to send:" << jsonData;

    // 发送注册请求
    manager->post(request, jsonData);
}

void RegisterController::onRegisterReplyFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        // 解析 JSON 响应
        QByteArray response = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
        QJsonObject jsonObject = jsonResponse.object();

        int result = jsonObject["result"].toInt();
        QString errorMsg = jsonObject["errorMsg"].toString();

        if (result == 1) {
            qDebug() << "[DEBUG] Registration successful for user:" << jsonObject["name"].toString();
            emit finishedRegisterUISignal("注册成功，欢迎使用！");
        } else {
            qDebug() << "[DEBUG] Registration failed:" << errorMsg;
            emit finishedRegisterUISignal("注册失败：" + errorMsg);
        }
    }
    else
    {
        qDebug() << "[ERROR] Network error:" << reply->errorString();
        emit finishedRegisterUISignal("网络错误，请稍后再试。");
    }
    reply->deleteLater();
}
