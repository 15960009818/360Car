#ifndef REGISTERCONTROLLER_H
#define REGISTERCONTROLLER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>

struct RegisterData {
    QString account;   // 用户账号
    QString name;      // 用户昵称
    QString password;  // 用户密码
};

class RegisterController : public QObject
{
    Q_OBJECT

public:
    RegisterController();
    ~RegisterController();

    void registerUser(const RegisterData &data); // 用户注册

signals:
    void finishedRegisterUISignal(const QString &uiMessage); // 注册结果信号

private slots:
    void onRegisterReplyFinished(QNetworkReply *reply); // 处理注册请求的回复

private:
    QNetworkAccessManager *manager; // 网络访问管理器
};

#endif // REGISTERCONTROLLER_H
