#include "logincontroller.h"
#include <QCryptographicHash>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include "../common/commondefs.h"

LoginController::LoginController() : manager(new QNetworkAccessManager(this))
{
    initController();
    connect(manager, &QNetworkAccessManager::finished, this, &LoginController::onReplyFinished);
}

LoginController::~LoginController()
{
    qDebug() << "[DEBUG] LoginController destroyed.";
}

int LoginController::getLoginFlag() const {
    return loginflag;
}

void LoginController::setLoginFlag(int flag) {
    qDebug() << "[DEBUG] Setting login flag to:" << flag;
    loginflag = flag;
}

/**
 * @brief LoginController::initController 初始化信号与槽
 */
void LoginController::initController()
{
    qDebug() << "[DEBUG] Initializing LoginController...";
    connect(this, SIGNAL(startedLoginSignal()), this, SLOT(startLoginSlot()));
    connect(this, SIGNAL(LoginCheckSignals(const QString&, const QString&, const QString&, const QString&)),
               this, SLOT(LoginCheckSlots(const QString&, const QString&, const QString&, const QString&)));
    connect(this, SIGNAL(finishedLoginControllerSignal(int)),
                this, SLOT(finishedLoginControllerThreadSlot(int)), Qt::QueuedConnection);
}

/**
 * @brief LoginController::LoginCheckSlots 登录验证槽
 * @param userAccount 用户账号
 * @param userPassword 用户密码
 * @param inputVerificationCode 用户输入的验证码
 * @param generatedVerificationCode 生成的验证码
 */
void LoginController::LoginCheckSlots(const QString &userAccount, const QString &userPassword, const QString &inputVerificationCode, const QString &generatedVerificationCode)
{
    qDebug() << "[DEBUG] LoginCheckSlots called.";

    // 检查用户输入是否为空
    if (userAccount.isEmpty() || userPassword.isEmpty() || inputVerificationCode.isEmpty()) {
        qDebug() << "[ERROR] 账号、密码或验证码不能为空";
        emit finishedLoginControllerSignal(USERINPUTEMPTY);
        return;
    }

    // 验证码检查
    if (inputVerificationCode != generatedVerificationCode) {
        qDebug() << "[ERROR] 验证码错误";
        emit finishedLoginControllerSignal(VERERROR);
        return;
    }

    // MD5加密
    QString encryptedPassword = QString(QCryptographicHash::hash(userPassword.toUtf8(), QCryptographicHash::Md5).toHex());
    qDebug() << "[DEBUG] Encrypted password (MD5):" << encryptedPassword;

    // 设置URL
    QUrl url("https://XiangJun.666/login");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // 创建 JSON 数据
    QJsonObject json;
    json["tel"] = userAccount;
    json["password"] = encryptedPassword;

    QJsonDocument jsonDoc(json);
    QByteArray jsonData = jsonDoc.toJson();
    qDebug() << "[DEBUG] JSON data to send:" << jsonData;

    qDebug() << "[DEBUG] Sending login request...";
    manager->post(request, jsonData);
}



/**
 * @brief LoginController::onReplyFinished 处理服务器返回的登录结果
 * @param reply 网络请求的返回结果
 */
void LoginController::onReplyFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        // 解析 JSON 响应
        QByteArray response = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response);
        QJsonObject jsonObject = jsonResponse.object();

        int result = jsonObject["result"].toInt();
        QString loginUserAccount = jsonObject["loginUserAccount"].toString();
        QString errorMsg = jsonObject["errorMsg"].toString();

        if (result == 1) {
            qDebug() << "[DEBUG] Login successful for user:" << loginUserAccount;

            // 检查是否有视频列表数据
            QJsonArray videoList = jsonObject["videoList"].toArray();
            qDebug() << "[DEBUG] Video list received, count:" << videoList.size();
            for (const QJsonValue &value : videoList) {
                QJsonObject videoObject = value.toObject();
                // 示例：解析视频对象
                qDebug() << "[DEBUG] Video object:" << videoObject;
            }

            emit finishedLoginControllerSignal(LOGINSUCCESS);
        } else {
            qDebug() << "[DEBUG] Login failed:" << errorMsg;
            emit finishedLoginControllerSignal(LOGINERROR);
        }
    }
    else
    {
        qDebug() << "[ERROR] Network error:" << reply->errorString();
        emit finishedLoginControllerSignal(SQLERROR);
    }
    reply->deleteLater();
}


/**
 * @brief LoginController::startLoginSlot 初始化槽函数
 */
void LoginController::startLoginSlot()
{
    qDebug() << "[DEBUG] Login process started.";
    setLoginFlag(0);
}

/**
 * @brief LoginController::finishedLoginControllerThreadSlot 返回登录结果给UI的槽
 * @param messageflag 登录验证信息
 */
void LoginController::finishedLoginControllerThreadSlot(const int messageflag)
{
    qDebug() << "[DEBUG] Login process finished, message flag:" << messageflag;

    QString uiMessage;

    // 根据 messageflag 解析不同的消息
    switch (messageflag) {
        case SQLERROR:
            uiMessage = "网络错误，请稍后再试。";
            break;
        case LOGINSUCCESS:
            uiMessage = "登录成功，欢迎使用！";
            break;
        case LOGINERROR:
            uiMessage = "登录失败，用户名或密码错误。";
            break;
        case USERINPUTEMPTY:
            uiMessage = "用户输入不能为空。";
            break;
        case VERERROR:
            uiMessage = "验证错误，请检查输入。";
            break;
        default:
            uiMessage = "发生未知错误。";
            break;
    }


    emit finishedLoginUISignal(uiMessage);
    qDebug() << "[DEBUG] emit finishedLoginUISignal:" << uiMessage;
}
