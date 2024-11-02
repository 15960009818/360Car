#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonArray>
#include "../common/singleton.h"

class LoginController : public QObject
{
    Q_OBJECT
    SINGLETON(LoginController)

signals:
    /**
     * @brief 发射信号用于登录检查
     * @param userAccount 用户账号
     * @param userPassword 用户密码
     * @param inputVerificationCode 用户输入的验证码
     * @param generatedVerificationCode 生成的验证码
     */
    void LoginCheckSignals(const QString& userAccount, const QString& userPassword, const QString& inputVerificationCode, const QString& generatedVerificationCode);

    /**
     * @brief 登录启动信号
     */
    void startedLoginSignal();

    /**
     * @brief 登录完成后向UI发出登录结果的信号
     * @param uiMessage UI提示信息
     */
    void finishedLoginUISignal(const QString &uiMessage);

    /**
     * @brief 登录控制器信号，用于传递结果状态
     * @param messageflag 状态标识
     */
    void finishedLoginControllerSignal(const int messageflag);

public:
    /**
     * @brief 初始化控制器
     */
    void initController();

    /**
     * @brief 获取当前登录标识状态
     * @return 登录标识
     */
    int getLoginFlag() const;

    /**
     * @brief 设置登录标识状态
     * @param flag 要设置的标识值
     */
    void setLoginFlag(int flag);

public slots:
    /**
     * @brief 登录检查槽函数
     * @param userAccount 用户账号
     * @param userPassword 用户密码
     * @param inputVerificationCode 用户输入的验证码
     * @param generatedVerificationCode 生成的验证码
     */
    void LoginCheckSlots(const QString& userAccount, const QString& userPassword, const QString& inputVerificationCode, const QString& generatedVerificationCode);

private:
    int loginflag;  ///< 登录状态标志
    QNetworkAccessManager *manager;  ///< 网络管理器指针

private slots:
    /**
     * @brief 初始化槽，用于开始登录
     */
    void startLoginSlot();

    /**
     * @brief 登录线程完成槽，用于返回登录结果
     * @param messageflag 登录验证信息标志
     */
    void finishedLoginControllerThreadSlot(const int messageflag);

    /**
     * @brief 处理服务器返回的登录结果槽
     * @param reply 网络请求返回结果
     */
    void onReplyFinished(QNetworkReply *reply);
};

#endif // LOGINCONTROLLER_H
