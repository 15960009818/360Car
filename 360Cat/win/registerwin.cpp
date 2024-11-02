#include "registerwin.h"
#include "ui_registerwin.h"

#include <QMessageBox>
#include <QCryptographicHash>
#include <controller/registercontroller.h>

RegisterWin::RegisterWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterWin),
    passwordVisible(false),
    confirmPasswordVisible(false)
{
    ui->setupUi(this);
}

RegisterWin::~RegisterWin()
{
    delete ui;
}

void RegisterWin::on_nameEdit_cursorPositionChanged(int arg1, int arg2) {}

void RegisterWin::on_lineEdit_2_cursorPositionChanged(int arg1, int arg2) {}

void RegisterWin::on_passwordEdit_cursorPositionChanged(int arg1, int arg2) {}

void RegisterWin::on_repasswordEdit_cursorPositionChanged(int arg1, int arg2) {}

// 切换密码显示状态
void RegisterWin::togglePasswordVisibility() {
    bool isPasswordHidden = (ui->passwordEdit->echoMode() == QLineEdit::Password);
    ui->passwordEdit->setEchoMode(isPasswordHidden ? QLineEdit::Normal : QLineEdit::Password);
    ui->repasswordEdit->setEchoMode(isPasswordHidden ? QLineEdit::Normal : QLineEdit::Password);
}

// 点击确定按钮后的处理逻辑
void RegisterWin::on_okBtn_clicked()
{
    QString account = ui->nameEdit->text();
    QString username = ui->lineEdit_2->text();
    QString password = ui->passwordEdit->text();
    QString confirmPassword = ui->repasswordEdit->text();

    // 参数验证
    if (!validateAccount(account) || !validateUsername(username) || !validatePassword(password, confirmPassword)) {
        return;  // 验证失败，退出
    }

    // MD5 加密密码
    QString encryptedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Md5).toHex());

    // 创建注册数据结构体并赋值
    RegisterData registerData;
    registerData.account = account;
    registerData.name = username;
    registerData.password = encryptedPassword;

    //Controller 发送注册请求
    RegisterController controller;
    connect(&controller, &RegisterController::finishedRegisterUISignal, this, [this](const QString &uiMessage) {
        QMessageBox::information(this, "注册结果", uiMessage);
        this->close();
    });

    controller.registerUser(registerData); // 使用结构体进行注册请求
}

// 点击取消按钮返回登录界面
void RegisterWin::on_cannelBtn_clicked()
{
    this->close();
}

// 账号验证
bool RegisterWin::validateAccount(const QString &account) {
    QRegExp accountRegex("^[A-Za-z0-9_]{6,8}$");
    if (!accountRegex.exactMatch(account)) {
        QMessageBox::warning(this, "输入错误", "账号只能包含英文大小写、数字、下划线，长度为6~8位。");
        return false;
    }
    return true;
}

// 用户名验证
bool RegisterWin::validateUsername(const QString &username) {
    QRegExp usernameRegex("^[\u4e00-\u9fa5A-Za-z0-9]{6,8}$");
    if (!usernameRegex.exactMatch(username)) {
        QMessageBox::warning(this, "输入错误", "用户名只能包含中英文大小写和数字，长度为6~8位。");
        return false;
    }
    return true;
}

// 密码验证
bool RegisterWin::validatePassword(const QString &password, const QString &confirmPassword) {
    QRegExp passwordRegex("^[A-Za-z0-9_]{6,10}$");
    if (!passwordRegex.exactMatch(password)) {
        QMessageBox::warning(this, "输入错误", "密码只能包含英文大小写、数字、下划线，长度为6~10位。");
        return false;
    }
    if (password != confirmPassword) {
        QMessageBox::warning(this, "输入错误", "两次输入的密码不一致。");
        return false;
    }
    return true;
}

void RegisterWin::on_showHidePasswordBtn2_clicked()
{
    // 切换密码框的显示模式
    passwordVisible = !passwordVisible;
    ui->passwordEdit->setEchoMode(passwordVisible ? QLineEdit::Normal : QLineEdit::Password);
    ui->showHidePasswordBtn->setText(passwordVisible ? "隐藏密码" : "显示密码");
}

void RegisterWin::on_showHidePasswordBtn_clicked()
{
    // 切换确认密码框的显示模式
    confirmPasswordVisible = !confirmPasswordVisible;
    ui->repasswordEdit->setEchoMode(confirmPasswordVisible ? QLineEdit::Normal : QLineEdit::Password);
    ui->showHidePasswordBtn2->setText(confirmPasswordVisible ? "隐藏密码" : "显示密码");
}
