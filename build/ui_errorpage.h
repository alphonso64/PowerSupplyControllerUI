/********************************************************************************
** Form generated from reading UI file 'errorpage.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ERRORPAGE_H
#define UI_ERRORPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ErrorPage
{
public:
    QLabel *label;

    void setupUi(QWidget *ErrorPage)
    {
        if (ErrorPage->objectName().isEmpty())
            ErrorPage->setObjectName(QStringLiteral("ErrorPage"));
        ErrorPage->resize(1024, 768);
        label = new QLabel(ErrorPage);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 180, 1021, 181));
        QFont font;
        font.setPointSize(48);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setStyleSheet(QStringLiteral("color: rgb(255, 17, 17);"));

        retranslateUi(ErrorPage);

        QMetaObject::connectSlotsByName(ErrorPage);
    } // setupUi

    void retranslateUi(QWidget *ErrorPage)
    {
        ErrorPage->setWindowTitle(QApplication::translate("ErrorPage", "Form", 0));
        label->setText(QApplication::translate("ErrorPage", "\347\264\247\346\200\245\345\201\234\346\234\272", 0));
    } // retranslateUi

};

namespace Ui {
    class ErrorPage: public Ui_ErrorPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ERRORPAGE_H
