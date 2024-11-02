/********************************************************************************
** Form generated from reading UI file 'registerwin.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERWIN_H
#define UI_REGISTERWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterWin
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *nameEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *passwordEdit;
    QLineEdit *repasswordEdit;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *okBtn;
    QPushButton *cannelBtn;
    QRadioButton *showHidePasswordBtn;
    QRadioButton *showHidePasswordBtn2;

    void setupUi(QWidget *RegisterWin)
    {
        if (RegisterWin->objectName().isEmpty())
            RegisterWin->setObjectName(QStringLiteral("RegisterWin"));
        RegisterWin->resize(472, 334);
        verticalLayoutWidget = new QWidget(RegisterWin);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(30, 30, 411, 201));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        nameEdit = new QLineEdit(verticalLayoutWidget);
        nameEdit->setObjectName(QStringLiteral("nameEdit"));

        verticalLayout->addWidget(nameEdit);

        lineEdit_2 = new QLineEdit(verticalLayoutWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        verticalLayout->addWidget(lineEdit_2);

        passwordEdit = new QLineEdit(verticalLayoutWidget);
        passwordEdit->setObjectName(QStringLiteral("passwordEdit"));

        verticalLayout->addWidget(passwordEdit);

        repasswordEdit = new QLineEdit(verticalLayoutWidget);
        repasswordEdit->setObjectName(QStringLiteral("repasswordEdit"));

        verticalLayout->addWidget(repasswordEdit);

        horizontalLayoutWidget = new QWidget(RegisterWin);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(30, 240, 411, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        okBtn = new QPushButton(horizontalLayoutWidget);
        okBtn->setObjectName(QStringLiteral("okBtn"));

        horizontalLayout->addWidget(okBtn);

        cannelBtn = new QPushButton(horizontalLayoutWidget);
        cannelBtn->setObjectName(QStringLiteral("cannelBtn"));

        horizontalLayout->addWidget(cannelBtn);

        showHidePasswordBtn = new QRadioButton(RegisterWin);
        showHidePasswordBtn->setObjectName(QStringLiteral("showHidePasswordBtn"));
        showHidePasswordBtn->setGeometry(QRect(450, 190, 69, 15));
        showHidePasswordBtn2 = new QRadioButton(RegisterWin);
        showHidePasswordBtn2->setObjectName(QStringLiteral("showHidePasswordBtn2"));
        showHidePasswordBtn2->setGeometry(QRect(450, 140, 69, 15));

        retranslateUi(RegisterWin);

        QMetaObject::connectSlotsByName(RegisterWin);
    } // setupUi

    void retranslateUi(QWidget *RegisterWin)
    {
        RegisterWin->setWindowTitle(QApplication::translate("RegisterWin", "Form", Q_NULLPTR));
        nameEdit->setText(QApplication::translate("RegisterWin", "\350\264\246\345\217\267", Q_NULLPTR));
        lineEdit_2->setText(QApplication::translate("RegisterWin", "\347\224\250\346\210\267\345\220\215/\346\230\265\347\247\260", Q_NULLPTR));
        passwordEdit->setText(QApplication::translate("RegisterWin", "\345\257\206\347\240\201", Q_NULLPTR));
        repasswordEdit->setText(QApplication::translate("RegisterWin", "\347\241\256\350\256\244\345\257\206\347\240\201", Q_NULLPTR));
        okBtn->setText(QApplication::translate("RegisterWin", "\347\241\256\345\256\232", Q_NULLPTR));
        cannelBtn->setText(QApplication::translate("RegisterWin", "\345\217\226\346\266\210", Q_NULLPTR));
        showHidePasswordBtn->setText(QString());
        showHidePasswordBtn2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class RegisterWin: public Ui_RegisterWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERWIN_H
