// settingwin.cpp
#include "menulist.h"
#include "ui_settingwin.h"
#include <QMessageBox>
#include <QIntValidator>

SettingWin::SettingWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWin),
    controller(new SettingController(this))
{
    ui->setupUi(this);

    // 设置 IP 和端口输入的验证器
    QIntValidator *ipValidator = new QIntValidator(0, 255, this);
    ui->ipFirstEdit->setValidator(ipValidator);
    ui->ipSecondEdit->setValidator(ipValidator);
    ui->ipThirdEdit->setValidator(ipValidator);
    ui->ipForthEdit->setValidator(ipValidator);

    QIntValidator *portValidator = new QIntValidator(1, 65535, this);
    ui->serverPortEdit->setValidator(portValidator);

    // 加载配置并填充编辑框
    loadSettings();

    // 连接网络验证结果的信号槽
    connect(controller, &SettingController::networkConnectionResult, this, &SettingWin::handleNetworkConnectionResult);
}

SettingWin::~SettingWin()
{
    delete ui;
}
void on_ipFirstEdit_cursorPositionChanged(int, int){};
void on_ipSecondEdit_cursorPositionChanged(int, int){};
void on_ipThirdEdit_cursorPositionChanged(int, int){};
void on_ipForthEdit_cursorPositionChanged(int, int){};
void on_serverPortEdit_cursorPositionChanged(int, int){};
void on_storageSizeEdit_cursorPositionChanged(int, int){};
void SettingWin::loadSettings()
{
    // 从控制器中获取并加载设置
    QStringList ipParts = controller->getIpAddress().split('.');
    if (ipParts.size() == 4) {
        ui->ipFirstEdit->setText(ipParts[0]);
        ui->ipSecondEdit->setText(ipParts[1]);
        ui->ipThirdEdit->setText(ipParts[2]);
        ui->ipForthEdit->setText(ipParts[3]);
    }

    ui->serverPortEdit->setText(QString::number(controller->getPort()));
    ui->storageSizeEdit->setText(QString::number(controller->getStorageSize()));
}

void SettingWin::on_saveButton_clicked()
{
    // 验证 IP 地址是否完整
    if (ui->ipFirstEdit->text().isEmpty() || ui->ipSecondEdit->text().isEmpty() ||
        ui->ipThirdEdit->text().isEmpty() || ui->ipForthEdit->text().isEmpty()) {
        QMessageBox::warning(this, "错误", "IP 地址不完整，请检查输入");
        return;
    }

    // 拼接完整的 IP 地址并验证
    QString ipAddress = QString("%1.%2.%3.%4")
                            .arg(ui->ipFirstEdit->text())
                            .arg(ui->ipSecondEdit->text())
                            .arg(ui->ipThirdEdit->text())
                            .arg(ui->ipForthEdit->text());

    QStringList ipParts = ipAddress.split('.');
    bool ipValid = true;
    for (const QString &part : ipParts) {
        int partValue = part.toInt();
        if (partValue < 0 || partValue > 255) {
            ipValid = false;
            break;
        }
    }

    if (!ipValid) {
        QMessageBox::warning(this, "错误", "IP 地址无效，请确保每个段的值在 0 到 255 之间");
        return;
    }

    // 验证端口
    int port = ui->serverPortEdit->text().toInt();
    if (port < 1 || port > 65535) {
        QMessageBox::warning(this, "错误", "端口号无效，请输入 1 到 65535 之间的值");
        return;
    }

    // 验证存储空间大小
    int storageSize = ui->storageSizeEdit->text().toInt();
    if (storageSize <= 0) {
        QMessageBox::warning(this, "错误", "存储空间大小无效，请输入正整数值");
        return;
    }

    // 保存到控制器（同时保存到配置文件）
    controller->setIpAddress(ipAddress);
    controller->setPort(port);
    controller->setStorageSize(storageSize);
    controller->saveSettings();

    // 显示保存成功的提示
    QMessageBox::information(this, "保存成功", "配置已成功保存！");

    // 调用网络连接测试
    on_verifyConnectionButton_clicked();
}


void SettingWin::on_verifyConnectionButton_clicked()
{
    // 获取 IP 地址和端口
    QString ipAddress = QString("%1.%2.%3.%4")
                            .arg(ui->ipFirstEdit->text())
                            .arg(ui->ipSecondEdit->text())
                            .arg(ui->ipThirdEdit->text())
                            .arg(ui->ipForthEdit->text());
    int port = ui->serverPortEdit->text().toInt();

    // 验证网络连接
    controller->verifyNetworkConnection(ipAddress, port);
}

void SettingWin::handleNetworkConnectionResult(bool success, const QString &message)
{
    // 根据结果显示提示信息
    if (success) {
        QMessageBox::information(this, "连接成功", message);
    } else {
        QMessageBox::warning(this, "连接失败", message);
    }
}
