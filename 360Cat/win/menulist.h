// settingwin.h
#ifndef SETTINGWIN_H
#define SETTINGWIN_H

#include <QWidget>
#include "../controller/settingcontroller.h"

namespace Ui {
class SettingWin;
}

class SettingWin : public QWidget
{
    Q_OBJECT

public:
    explicit SettingWin(QWidget *parent = nullptr);
    ~SettingWin();

private slots:
    void loadSettings();
    void on_saveButton_clicked();
    void on_verifyConnectionButton_clicked();
    void handleNetworkConnectionResult(bool success, const QString &message);


    void on_ipFirstEdit_cursorPositionChanged(int, int);
    void on_ipSecondEdit_cursorPositionChanged(int, int);
    void on_ipThirdEdit_cursorPositionChanged(int, int);
    void on_ipForthEdit_cursorPositionChanged(int, int);
    void on_serverPortEdit_cursorPositionChanged(int, int);
    void on_storageSizeEdit_cursorPositionChanged(int, int);

private:
    Ui::SettingWin *ui;
    SettingController *controller;
};

#endif // SETTINGWIN_H
