/********************************************************************************
** Form generated from reading UI file 'actiondialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACTIONDIALOG_H
#define UI_ACTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ActionDialog
{
public:
    QPushButton *doneButton;
    QPushButton *rejectButton;
    QListView *listView;

    void setupUi(QDialog *ActionDialog)
    {
        if (ActionDialog->objectName().isEmpty())
            ActionDialog->setObjectName(QStringLiteral("ActionDialog"));
        ActionDialog->resize(640, 480);
        doneButton = new QPushButton(ActionDialog);
        doneButton->setObjectName(QStringLiteral("doneButton"));
        doneButton->setGeometry(QRect(500, 20, 131, 61));
        QFont font;
        font.setPointSize(18);
        doneButton->setFont(font);
        doneButton->setFocusPolicy(Qt::ClickFocus);
        rejectButton = new QPushButton(ActionDialog);
        rejectButton->setObjectName(QStringLiteral("rejectButton"));
        rejectButton->setGeometry(QRect(500, 110, 131, 61));
        rejectButton->setFont(font);
        rejectButton->setFocusPolicy(Qt::ClickFocus);
        listView = new QListView(ActionDialog);
        listView->setObjectName(QStringLiteral("listView"));
        listView->setGeometry(QRect(10, 20, 481, 441));
        listView->setFont(font);

        retranslateUi(ActionDialog);

        QMetaObject::connectSlotsByName(ActionDialog);
    } // setupUi

    void retranslateUi(QDialog *ActionDialog)
    {
        ActionDialog->setWindowTitle(QApplication::translate("ActionDialog", "Dialog", 0));
        doneButton->setText(QApplication::translate("ActionDialog", "\347\241\256\345\256\232", 0));
        rejectButton->setText(QApplication::translate("ActionDialog", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class ActionDialog: public Ui_ActionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACTIONDIALOG_H
