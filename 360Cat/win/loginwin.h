#ifndef LOGINWIN_H
#define LOGINWIN_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include "../common/verificationcodelabel.h"
#include "../controller/logincontroller.h"

/**
 * @类名: LoginWin
 * @描述: 登录窗口类，用于用户登录界面的展示和交互
 * @作者: 翔君
 * @创建日期: 2024/9/14
 * @是否完成:
 */
class LoginWin : public QWidget
{
    Q_OBJECT
public:
    /**
     * @函数名: LoginWin
     * @作者: 翔君
     * @创建日期: 2024/9/14
     * @是否完成:
     */
    explicit LoginWin(QWidget *parent = nullptr);

    /**
     * @函数名: setUi
     * @描述: 设置登录窗口的UI界面布局
     * @作者: 翔君
     * @创建日期: 2024/9/14
     * @是否完成:
     */
    void setUi();

    /**
     * @函数名: connectSignals
     * @描述: 连接登录窗口的信号与槽函数
     * @作者: 翔君
     * @创建日期: 2024/9/14
     * @是否完成:
     */
    void connectSignals();

private slots:
    /**
     * @函数名: BtnClicked
     * @描述: 处理按钮点击事件的槽函数
     * @作者: 翔君
     * @创建日期: 2024/9/14
     * @是否完成:
     */
    void BtnClicked();

private:
    QLabel *labTitle;                /**< 登录窗口的标题标签 */
    QLabel *labUserId;               /**< 用户账号标签 */
    QLabel *labPwd;                  /**< 密码标签 */
    QLabel *labVfcd;                 /**< 验证码标签 */
    QLineEdit *editUserId;           /**< 用户账号输入框 */
    QLineEdit *editPwd;              /**< 密码输入框 */
    QLineEdit *editVfcd;             /**< 验证码输入框 */
    VerificationCodeLabel *labVerificationCode;  /**< 验证码类 */
    QPushButton *btnOk;              /**< 确认按钮 */
    QPushButton *btnReset;           /**< 重置按钮 */
    QPushButton *btnCancel;          /**< 取消按钮 */
    QPushButton *btnShowPwd;         /**< 显示密码按钮 */
    QLabel      *labAccount;
    QGridLayout *gridLayout;         /**< 网格布局管理器 */
    QVBoxLayout *mainLayout;         /**< 垂直布局管理器 */
    QLineEdit   *editAccount;
private slots:
    /**
     * @函数名: showLoginControllerResultUISlot
     * @描述: 显示登录结果的槽函数
     * @参数: uiMessage 包含登录结果的消息
     * @作者: 翔君
     * @创建日期: 2024/9/14
     * @是否完成:
     */
    void showLoginControllerResultUISlot(const QString &uiMessage);
};

#endif // LOGINWIN_H
