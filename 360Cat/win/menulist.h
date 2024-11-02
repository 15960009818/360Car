#ifndef SETTINGWIN_H
#define SETTINGWIN_H

#include <QWidget>

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
    void on_ipFirstEdit_cursorPositionChanged(int arg1, int arg2);

    void on_ipSecondEdit_cursorPositionChanged(int arg1, int arg2);

    void on_ipForthEdit_cursorPositionChanged(int arg1, int arg2);

    void on_ipThirdEdit_cursorPositionChanged(int arg1, int arg2);

    void on_serverPortEdit_cursorPositionChanged(int arg1, int arg2);

    void on_storageSizeEdit_cursorPositionChanged(int arg1, int arg2);

    void on_saveButton_clicked();

private:
    Ui::SettingWin *ui;
};

#endif // SETTINGWIN_H
