#ifndef REGISTERWIN_H
#define REGISTERWIN_H

#include <QWidget>

namespace Ui {
class RegisterWin;
}

class RegisterWin : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWin(QWidget *parent = nullptr);
    ~RegisterWin();

private slots:
    void on_nameEdit_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_2_cursorPositionChanged(int arg1, int arg2);

    void on_passwordEdit_cursorPositionChanged(int arg1, int arg2);

    void on_repasswordEdit_cursorPositionChanged(int arg1, int arg2);

    void on_okBtn_clicked();

    void on_cannelBtn_clicked();

    void on_showHidePasswordBtn_clicked();  // 密码框的明文/密文切换
    void on_showHidePasswordBtn2_clicked(); // 确认密码框的明文/密文切换

private:
    Ui::RegisterWin *ui;
    bool validateAccount(const QString &account);
    bool validateUsername(const QString &username);
    bool validatePassword(const QString &password);
    bool validatePassword(const QString &password, const QString &confirmPassword);
    void togglePasswordVisibility();
    bool passwordVisible = false;         // 控制密码框显示模式的布尔变量
    bool confirmPasswordVisible = false;   // 控制确认密码框显示模式的布尔变量
};

#endif // REGISTERWIN_H
