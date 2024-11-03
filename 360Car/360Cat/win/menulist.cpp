#include "settingwin.h"
#include "ui_settingwin.h"
#include "settingcontroller.h"
#include <QMessageBox>
#include <QIntValidator>

SettingWin::SettingWin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingWin),
    controller(new SettingController(this)) // 初始化 SettingController
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
}

SettingWin::~SettingWin()
{
    delete ui;
}

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

void SettingWin::on_ipFirstEdit_cursorPositionChanged(int, int) { /* 可添加其他处理逻辑 */ }
void SettingWin::on_ipSecondEdit_cursorPositionChanged(int, int) { /* 可添加其他处理逻辑 */ }
void SettingWin::on_ipThirdEdit_cursorPositionChanged(int, int) { /* 可添加其他处理逻辑 */ }
void SettingWin::on_ipForthEdit_cursorPositionChanged(int, int) { /* 可添加其他处理逻辑 */ }
void SettingWin::on_serverPortEdit_cursorPositionChanged(int, int) { /* 可添加其他处理逻辑 */ }
void SettingWin::on_storageSizeEdit_cursorPositionChanged(int, int) { /* 可添加其他处理逻辑 */ }

void SettingWin::on_saveButton_clicked()
{
    // 验证 IP 输入是否完整
    if (ui->ipFirstEdit->text().isEmpty() || ui->ipSecondEdit->text().isEmpty() ||
        ui->ipThirdEdit->text().isEmpty() || ui->ipForthEdit->text().isEmpty()) {
        QMessageBox::warning(this, "错误", "IP 地址不完整，请检查输入");
        return;
    }

    // 拼接完整的 IP 地址
    QString ipAddress = QString("%1.%2.%3.%4")
                            .arg(ui->ipFirstEdit->text())
                            .arg(ui->ipSecondEdit->text())
                            .arg(ui->ipThirdEdit->text())
                            .arg(ui->ipForthEdit->text());

    // 获取并验证端口和存储大小
    int port = ui->serverPortEdit->text().toInt();
    int storageSize = ui->storageSizeEdit->text().toInt();

    // 保存到控制器（同时保存到配置文件）
    controller->setIpAddress(ipAddress);
    controller->setPort(port);
    controller->setStorageSize(storageSize);
    controller->saveSettings();

    // 显示保存成功的提示
    QMessageBox::information(this, "保存成功", "配置已成功保存！");
}
