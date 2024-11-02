#include "loginwin.h"
#include <QMessageBox>

LoginWin::LoginWin(QWidget *parent)
{
    setUi();
    connectSignals();
}

/**
 * @brief LoginWin::setUi 登录页面
 */
void LoginWin::setUi() {
    this->setFixedSize(400, 600);
    this->setWindowTitle("登录界面");

    labTitle = new QLabel("登录界面", this);
    labAccount = new QLabel("账号", this);  // 将设备编号标签改为账号标签
    labPwd = new QLabel("密码", this);
    labVfcd = new QLabel("验证码", this);

    editAccount = new QLineEdit(this);  // 创建账号编辑栏
    editAccount->setPlaceholderText("请输入账号");

    editPwd = new QLineEdit(this);
    editPwd->setEchoMode(QLineEdit::Password);
    editPwd->setPlaceholderText("请输入密码");

    editVfcd = new QLineEdit(this);
    editVfcd->setPlaceholderText("请输入验证码");

    // 验证码图片
    labVerificationCode = new VerificationCodeLabel(this);
    labVerificationCode->setFixedSize(80, 30);  // 设置验证码图片大小

    // 确认、重置和取消按钮
    btnOk = new QPushButton("确定", this);
    btnReset = new QPushButton("清空", this);
    btnCancel = new QPushButton("取消", this);

    // 显示密码按钮
    btnShowPwd = new QPushButton(this);
    btnShowPwd->setFixedSize(22, 22);
    btnShowPwd->setToolTip("密码可见");
    btnShowPwd->setCursor(Qt::PointingHandCursor);
    btnShowPwd->setStyleSheet("QPushButton{border-image:url(:/image/Login/眼睛_显示_o.png);background:transparent;}");

    // 为密码输入框设置边距
    QMargins margins = editPwd->textMargins();
    editPwd->setTextMargins(margins.left(), margins.top(), btnShowPwd->width(), margins.bottom());

    // 布局设置
    gridLayout = new QGridLayout;
    gridLayout->addWidget(labTitle, 0, 1, 1, 1);
    gridLayout->addWidget(labAccount, 1, 0, 1, 1);
    gridLayout->addWidget(editAccount, 1, 1, 1, 2);
    gridLayout->addWidget(labPwd, 2, 0, 1, 1);
    gridLayout->addWidget(editPwd, 2, 1, 1, 2);
    gridLayout->addWidget(btnShowPwd, 2, 2, 1, 1);
    gridLayout->addWidget(labVfcd, 3, 0, 1, 1);
    gridLayout->addWidget(editVfcd, 3, 1, 1, 1);
    gridLayout->addWidget(labVerificationCode, 3, 2, 1, 1);  // 验证码图片与输入框平行

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(btnOk);
    buttonLayout->addWidget(btnReset);
    buttonLayout->addWidget(btnCancel);

    mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(gridLayout);
    mainLayout->addLayout(buttonLayout);

    setLayout(mainLayout);
}

/**
 * @brief LoginWin::connectSignals 统一管理按钮信号
 */
void LoginWin::connectSignals()
{
    qDebug() << "[DEBUG] btnOk exists:" << btnOk;
    qDebug() << "[DEBUG] btnReset exists:" << btnReset;
    qDebug() << "[DEBUG] btnCancel exists:" << btnCancel;

    //号到 LoginWin
    connect(&Singleton<LoginController>::getInstance(),
            SIGNAL(finishedLoginUISignal(const QString &)),
            this, SLOT(showLoginControllerResultUISlot(const QString &)),
            Qt::QueuedConnection);

    // 确定按钮
    connect(btnOk, &QPushButton::clicked, this, &LoginWin::BtnClicked);
    // 重置清空按钮
    connect(btnReset, &QPushButton::clicked, this, &LoginWin::BtnClicked);
    // 取消按钮
    connect(btnCancel, &QPushButton::clicked, this, &LoginWin::BtnClicked);
}

/**
 * @brief LoginWin::BtnClicked 按钮功能槽
 * 根据不同按钮执行不同的操作
 */
void LoginWin::BtnClicked()
{
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());

    if (clickedButton == btnOk) {
        QString userId = editAccount->text();
        QString password = editPwd->text();
        QString inputVerificationCode = editVfcd->text();
        QString generatedVerificationCode = labVerificationCode->getVerificationCode();

        qDebug() << "[DEBUG] Account (User ID):" << userId;
        qDebug() << "[DEBUG] Password:" << password;
        qDebug() << "[DEBUG] Input Verification Code:" << inputVerificationCode;
        qDebug() << "[DEBUG] Generated Verification Code:" << generatedVerificationCode;

        emit Singleton<LoginController>::getInstance().LoginCheckSignals(userId, password, inputVerificationCode, generatedVerificationCode);
    } else if (clickedButton == btnReset) {
        editAccount->clear();
        editPwd->clear();
        editVfcd->clear();

        qDebug() << "[DEBUG] Input fields reset.";
    } else if (clickedButton == btnCancel) {
        qDebug() << "[DEBUG] Login canceled.";
        close();
    }
}

/**
 * @brief LoginWin::showLoginControllerResultUISlot
 * logincontroller结果弹出框
 * @param uiMessage
 */
void LoginWin::showLoginControllerResultUISlot(const QString &uiMessage)
{
   QMessageBox::information(this, "登录结果", uiMessage);
}
