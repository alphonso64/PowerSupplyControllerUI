/********************************************************************************
** Form generated from reading UI file 'cusdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSDIALOG_H
#define UI_CUSDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CusDialog
{
public:
    QPushButton *doneButton;
    QLabel *label;
    QPushButton *rejectButton;
    QPushButton *okayButton;

    void setupUi(QDialog *CusDialog)
    {
        if (CusDialog->objectName().isEmpty())
            CusDialog->setObjectName(QStringLiteral("CusDialog"));
        CusDialog->resize(640, 480);
        doneButton = new QPushButton(CusDialog);
        doneButton->setObjectName(QStringLiteral("doneButton"));
        doneButton->setGeometry(QRect(330, 390, 201, 71));
        QFont font;
        font.setPointSize(18);
        doneButton->setFont(font);
        doneButton->setFocusPolicy(Qt::NoFocus);
        label = new QLabel(CusDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 150, 640, 111));
        QFont font1;
        font1.setPointSize(24);
        label->setFont(font1);
        rejectButton = new QPushButton(CusDialog);
        rejectButton->setObjectName(QStringLiteral("rejectButton"));
        rejectButton->setGeometry(QRect(100, 390, 201, 71));
        rejectButton->setFont(font);
        rejectButton->setFocusPolicy(Qt::NoFocus);
        okayButton = new QPushButton(CusDialog);
        okayButton->setObjectName(QStringLiteral("okayButton"));
        okayButton->setGeometry(QRect(220, 390, 201, 71));
        okayButton->setFont(font);
        okayButton->setFocusPolicy(Qt::NoFocus);

        retranslateUi(CusDialog);

        QMetaObject::connectSlotsByName(CusDialog);
    } // setupUi

    void retranslateUi(QDialog *CusDialog)
    {
        CusDialog->setWindowTitle(QApplication::translate("CusDialog", "Dialog", 0));
        doneButton->setText(QApplication::translate("CusDialog", "\347\241\256\345\256\232", 0));
        label->setText(QString());
        rejectButton->setText(QApplication::translate("CusDialog", "\345\217\226\346\266\210", 0));
        okayButton->setText(QApplication::translate("CusDialog", "\347\241\256\345\256\232", 0));
    } // retranslateUi

};

namespace Ui {
    class CusDialog: public Ui_CusDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSDIALOG_H
