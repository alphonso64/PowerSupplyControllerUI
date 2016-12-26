/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *setButton;
    QPushButton *manualButton;
    QPushButton *autoButton;
    QPushButton *infoButton;
    QStackedWidget *stackedWidget;
    QWidget *setPage;
    QLabel *label_22;
    QLabel *label_23;
    QLabel *label_24;
    QLabel *label_25;
    QPushButton *setButton_2;
    QPushButton *setButton_3;
    QWidget *manualPage;
    QGroupBox *groupBox;
    QSlider *powerSlider;
    QLabel *label_16;
    QLabel *powerSliderLabel;
    QPushButton *manualStartButton;
    QLabel *label_20;
    QPushButton *manualactionAButton;
    QPushButton *manualactionBButton;
    QPushButton *manualactionCButton;
    QPushButton *manualactionDButton;
    QLabel *label_21;
    QLineEdit *timeEdit;
    QLabel *timeunitlabel;
    QLabel *manualtimelabel;
    QLabel *label_3;
    QWidget *dispalyWidget;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *displayTempLabel;
    QLabel *displayPowerLabel;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *displayWarningLabel;
    QLabel *displayControlLabel;
    QLabel *label_17;
    QLineEdit *fileNameEdit;
    QPushButton *recordStartButton;
    QWidget *autoPage;
    QLabel *fileNameText;
    QLabel *label_4;
    QWidget *dispalyWidget_2;
    QLabel *label_44;
    QLabel *label_43;
    QLabel *displayTempLabel_2;
    QLabel *displayPowerLabel_2;
    QLabel *label_46;
    QLabel *label_47;
    QLabel *label_48;
    QLabel *label_49;
    QLabel *displayWarningLabel_2;
    QLabel *displayControlLabel_2;
    QLabel *label_52;
    QGroupBox *groupBox_2;
    QPushButton *autoStartButton;
    QListView *autoListView;
    QLabel *autoStageTimeText;
    QLabel *autoStageText;
    QLabel *autoIndexText;
    QLabel *powerSliderLabel_2;
    QSlider *powerSlider_2;
    QLabel *label_18;
    QPushButton *openFileButton;
    QWidget *infoPage;
    QLabel *softVersionLabel;
    QLabel *label_26;
    QLabel *label_27;
    QLabel *label_28;
    QPushButton *softUpdateButton;
    QPushButton *restartButton;
    QPushButton *firmwareUpdateButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1024, 768);
        MainWindow->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setFocusPolicy(Qt::ClickFocus);
        centralWidget->setStyleSheet(QStringLiteral(";"));
        setButton = new QPushButton(centralWidget);
        setButton->setObjectName(QStringLiteral("setButton"));
        setButton->setGeometry(QRect(51, 650, 171, 121));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(24);
        setButton->setFont(font);
        setButton->setFocusPolicy(Qt::NoFocus);
        setButton->setStyleSheet(QLatin1String("QPushButton{background-color: rgba(84, 110, 122, 255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:disabled{color: rgb(0, 0, 0);background-color: rgba(38, 166, 154, 255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}"));
        manualButton = new QPushButton(centralWidget);
        manualButton->setObjectName(QStringLiteral("manualButton"));
        manualButton->setGeometry(QRect(301, 650, 171, 121));
        manualButton->setFont(font);
        manualButton->setFocusPolicy(Qt::NoFocus);
        manualButton->setStyleSheet(QLatin1String("QPushButton{background-color: rgba(84, 110, 122, 255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:disabled{color: rgb(0, 0, 0);background-color: rgba(38, 166, 154, 255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}"));
        autoButton = new QPushButton(centralWidget);
        autoButton->setObjectName(QStringLiteral("autoButton"));
        autoButton->setGeometry(QRect(551, 650, 171, 121));
        autoButton->setFont(font);
        autoButton->setFocusPolicy(Qt::NoFocus);
        autoButton->setStyleSheet(QLatin1String("QPushButton{background-color: rgba(84, 110, 122, 255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:disabled{color: rgb(0, 0, 0);background-color: rgba(38, 166, 154, 255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}"));
        infoButton = new QPushButton(centralWidget);
        infoButton->setObjectName(QStringLiteral("infoButton"));
        infoButton->setGeometry(QRect(801, 650, 171, 121));
        infoButton->setFont(font);
        infoButton->setFocusPolicy(Qt::NoFocus);
        infoButton->setStyleSheet(QLatin1String("QPushButton{background-color: rgba(84, 110, 122, 255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:disabled{color: rgb(0, 0, 0);background-color: rgba(38, 166, 154, 255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}"));
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setGeometry(QRect(20, 10, 984, 631));
        stackedWidget->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"border-color: rgb(0, 170, 0);\n"
"gridline-color: rgb(112, 255, 129);"));
        setPage = new QWidget();
        setPage->setObjectName(QStringLiteral("setPage"));
        label_22 = new QLabel(setPage);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(230, 55, 291, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(18);
        label_22->setFont(font1);
        label_22->setStyleSheet(QLatin1String("border: 2px solid rgb(0, 77, 64);\n"
"background-color: rgb(0, 150, 136);\n"
""));
        label_23 = new QLabel(setPage);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(60, 60, 161, 31));
        label_23->setFont(font1);
        label_24 = new QLabel(setPage);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(60, 145, 161, 31));
        label_24->setFont(font1);
        label_25 = new QLabel(setPage);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(230, 140, 291, 41));
        label_25->setFont(font1);
        label_25->setStyleSheet(QLatin1String("border: 2px solid rgb(0, 77, 64);\n"
"background-color: rgb(0, 150, 136);\n"
""));
        setButton_2 = new QPushButton(setPage);
        setButton_2->setObjectName(QStringLiteral("setButton_2"));
        setButton_2->setGeometry(QRect(610, 430, 111, 71));
        setButton_2->setFont(font1);
        setButton_2->setFocusPolicy(Qt::ClickFocus);
        setButton_2->setStyleSheet(QLatin1String("QPushButton{background-color: rgba(84, 110, 122, 255);  border: 1px solid rgb(124, 124, 124); border-radius:20px;}\n"
"QPushButton:checked{background-color: rgba(38, 166, 154, 255);  border: 1px solid rgb(124, 124, 124); border-radius:20px;}"));
        setButton_3 = new QPushButton(setPage);
        setButton_3->setObjectName(QStringLiteral("setButton_3"));
        setButton_3->setGeometry(QRect(780, 430, 111, 71));
        setButton_3->setFont(font1);
        setButton_3->setFocusPolicy(Qt::ClickFocus);
        setButton_3->setStyleSheet(QLatin1String("QPushButton{background-color: rgba(84, 110, 122, 255);  border: 1px solid rgb(124, 124, 124); border-radius:20px;}\n"
"QPushButton:checked{background-color: rgba(38, 166, 154, 255);  border: 1px solid rgb(124, 124, 124); border-radius:20px;}"));
        stackedWidget->addWidget(setPage);
        manualPage = new QWidget();
        manualPage->setObjectName(QStringLiteral("manualPage"));
        groupBox = new QGroupBox(manualPage);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(30, 200, 921, 381));
        groupBox->setFont(font1);
        groupBox->setStyleSheet(QLatin1String("QGroupBox {\n"
"background-color: qlineargradient(spread:pad, x1:0.489, y1:1, x2:0.505682, y2:0.17, stop:0 rgba(128, 203, 196, 255), stop:1 rgba(255, 255, 255, 255));\n"
"    border: 2px solid rgb(0, 77, 64);\n"
"    border-radius: 10px;\n"
"    margin-top: 1em;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 10px;\n"
"    padding: 0 3px 0 3px;\n"
"}"));
        groupBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        powerSlider = new QSlider(groupBox);
        powerSlider->setObjectName(QStringLiteral("powerSlider"));
        powerSlider->setGeometry(QRect(160, 270, 581, 41));
        powerSlider->setStyleSheet(QLatin1String("QSlider{\n"
"background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"QSlider::groove:horizontal { \n"
"height: 20px; \n"
"background: rgb(0, 150, 136); \n"
"margin: 2px 0; \n"
"} \n"
"QSlider::handle:horizontal { \n"
"background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f); \n"
"border: 1px solid #5c5c5c; \n"
"width: 30px; \n"
"margin: -8px 0px; \n"
"} "));
        powerSlider->setOrientation(Qt::Horizontal);
        label_16 = new QLabel(groupBox);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(50, 270, 101, 41));
        label_16->setFont(font1);
        label_16->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255, 0);"));
        powerSliderLabel = new QLabel(groupBox);
        powerSliderLabel->setObjectName(QStringLiteral("powerSliderLabel"));
        powerSliderLabel->setGeometry(QRect(760, 270, 121, 41));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(14);
        powerSliderLabel->setFont(font2);
        powerSliderLabel->setStyleSheet(QLatin1String("border: 2px solid rgb(0, 77, 64);\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(0, 150, 136);\n"
""));
        manualStartButton = new QPushButton(groupBox);
        manualStartButton->setObjectName(QStringLiteral("manualStartButton"));
        manualStartButton->setGeometry(QRect(50, 100, 111, 91));
        manualStartButton->setFont(font);
        manualStartButton->setFocusPolicy(Qt::NoFocus);
        manualStartButton->setStyleSheet(QLatin1String("QPushButton{background-color: rgba(38, 166, 154,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:pressed{background-color: rgba(0, 77, 64,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}"));
        label_20 = new QLabel(groupBox);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(180, 100, 51, 41));
        label_20->setFont(font1);
        label_20->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255, 0);"));
        manualactionAButton = new QPushButton(groupBox);
        manualactionAButton->setObjectName(QStringLiteral("manualactionAButton"));
        manualactionAButton->setGeometry(QRect(510, 100, 81, 91));
        manualactionAButton->setFont(font1);
        manualactionAButton->setFocusPolicy(Qt::NoFocus);
        manualactionAButton->setStyleSheet(QLatin1String("QPushButton{background-color: rgba(84, 110, 122, 255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:pressed{background-color: rgba(38, 166, 154, 255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}"));
        manualactionBButton = new QPushButton(groupBox);
        manualactionBButton->setObjectName(QStringLiteral("manualactionBButton"));
        manualactionBButton->setGeometry(QRect(610, 100, 81, 91));
        manualactionBButton->setFont(font1);
        manualactionBButton->setFocusPolicy(Qt::NoFocus);
        manualactionBButton->setStyleSheet(QLatin1String("QPushButton{background-color: rgba(84, 110, 122, 255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:pressed{background-color: rgba(38, 166, 154, 255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}"));
        manualactionCButton = new QPushButton(groupBox);
        manualactionCButton->setObjectName(QStringLiteral("manualactionCButton"));
        manualactionCButton->setGeometry(QRect(710, 100, 81, 91));
        QFont font3;
        font3.setFamily(QStringLiteral("Sans"));
        font3.setPointSize(18);
        manualactionCButton->setFont(font3);
        manualactionCButton->setFocusPolicy(Qt::NoFocus);
        manualactionCButton->setStyleSheet(QLatin1String("QPushButton{background-color: rgba(84, 110, 122, 255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:pressed{background-color: rgba(38, 166, 154, 255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}"));
        manualactionDButton = new QPushButton(groupBox);
        manualactionDButton->setObjectName(QStringLiteral("manualactionDButton"));
        manualactionDButton->setGeometry(QRect(810, 100, 81, 91));
        manualactionDButton->setFont(font1);
        manualactionDButton->setFocusPolicy(Qt::NoFocus);
        manualactionDButton->setStyleSheet(QLatin1String("QPushButton{background-color: rgba(84, 110, 122, 255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:pressed{background-color: rgba(38, 166, 154, 255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}"));
        label_21 = new QLabel(groupBox);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(460, 110, 31, 71));
        label_21->setFont(font1);
        label_21->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255, 0);"));
        timeEdit = new QLineEdit(groupBox);
        timeEdit->setObjectName(QStringLiteral("timeEdit"));
        timeEdit->setGeometry(QRect(240, 100, 151, 41));
        timeEdit->setFont(font1);
        timeEdit->setFocusPolicy(Qt::ClickFocus);
        timeEdit->setStyleSheet(QLatin1String("border: 2px solid rgb(0, 77, 64);\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(0, 150, 136);"));
        timeunitlabel = new QLabel(groupBox);
        timeunitlabel->setObjectName(QStringLiteral("timeunitlabel"));
        timeunitlabel->setGeometry(QRect(400, 100, 51, 41));
        timeunitlabel->setFont(font1);
        timeunitlabel->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255, 0);"));
        manualtimelabel = new QLabel(groupBox);
        manualtimelabel->setObjectName(QStringLiteral("manualtimelabel"));
        manualtimelabel->setGeometry(QRect(240, 150, 151, 41));
        manualtimelabel->setFont(font1);
        manualtimelabel->setStyleSheet(QStringLiteral("background-color: rgb(84, 110, 122);"));
        label_3 = new QLabel(manualPage);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(40, 50, 101, 31));
        label_3->setFont(font3);
        dispalyWidget = new QWidget(manualPage);
        dispalyWidget->setObjectName(QStringLiteral("dispalyWidget"));
        dispalyWidget->setGeometry(QRect(520, 10, 431, 171));
        dispalyWidget->setStyleSheet(QLatin1String("#dispalyWidget{background-color: rgb(84, 110, 122);\n"
"border: 2px solid rgb(0, 77, 64);\n"
"border-radius:10px;}"));
        label_6 = new QLabel(dispalyWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 60, 61, 31));
        label_6->setFont(font1);
        label_6->setStyleSheet(QLatin1String("background-color: rgb(84, 110, 122);\n"
"color: rgb(255, 255, 255);"));
        label_7 = new QLabel(dispalyWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 120, 61, 31));
        label_7->setFont(font1);
        label_7->setStyleSheet(QLatin1String("background-color: rgb(84, 110, 122);\n"
"color: rgb(255, 255, 255);"));
        displayTempLabel = new QLabel(dispalyWidget);
        displayTempLabel->setObjectName(QStringLiteral("displayTempLabel"));
        displayTempLabel->setGeometry(QRect(80, 60, 61, 31));
        displayTempLabel->setFont(font1);
        displayTempLabel->setStyleSheet(QLatin1String("background-color: rgb(84, 110, 122);\n"
"color: rgb(255, 255, 255);"));
        displayPowerLabel = new QLabel(dispalyWidget);
        displayPowerLabel->setObjectName(QStringLiteral("displayPowerLabel"));
        displayPowerLabel->setGeometry(QRect(80, 120, 61, 31));
        displayPowerLabel->setFont(font1);
        displayPowerLabel->setStyleSheet(QLatin1String("background-color: rgb(84, 110, 122);\n"
"color: rgb(255, 255, 255);"));
        label_10 = new QLabel(dispalyWidget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(150, 60, 31, 31));
        label_10->setFont(font1);
        label_10->setStyleSheet(QLatin1String("background-color: rgb(84, 110, 122);\n"
"color: rgb(255, 255, 255);"));
        label_11 = new QLabel(dispalyWidget);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(140, 120, 61, 31));
        label_11->setFont(font1);
        label_11->setStyleSheet(QLatin1String("background-color: rgb(84, 110, 122);\n"
"color: rgb(255, 255, 255);"));
        label_12 = new QLabel(dispalyWidget);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(210, 60, 121, 31));
        label_12->setFont(font1);
        label_12->setStyleSheet(QLatin1String("background-color: rgb(84, 110, 122);\n"
"color: rgb(255, 255, 255);"));
        label_13 = new QLabel(dispalyWidget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(210, 120, 121, 31));
        label_13->setFont(font1);
        label_13->setStyleSheet(QLatin1String("background-color: rgb(84, 110, 122);\n"
"color: rgb(255, 255, 255);"));
        displayWarningLabel = new QLabel(dispalyWidget);
        displayWarningLabel->setObjectName(QStringLiteral("displayWarningLabel"));
        displayWarningLabel->setGeometry(QRect(330, 60, 81, 31));
        displayWarningLabel->setFont(font1);
        displayWarningLabel->setStyleSheet(QLatin1String("background-color: rgb(84, 110, 122);\n"
"color: rgb(255, 255, 255);"));
        displayControlLabel = new QLabel(dispalyWidget);
        displayControlLabel->setObjectName(QStringLiteral("displayControlLabel"));
        displayControlLabel->setGeometry(QRect(330, 120, 81, 31));
        displayControlLabel->setFont(font1);
        displayControlLabel->setStyleSheet(QLatin1String("background-color: rgb(84, 110, 122);\n"
"color: rgb(255, 255, 255);"));
        label_17 = new QLabel(dispalyWidget);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(160, 10, 121, 31));
        label_17->setFont(font1);
        label_17->setStyleSheet(QLatin1String("background-color: rgb(84, 110, 122);\n"
"color: rgb(139, 195, 74);"));
        fileNameEdit = new QLineEdit(manualPage);
        fileNameEdit->setObjectName(QStringLiteral("fileNameEdit"));
        fileNameEdit->setGeometry(QRect(160, 45, 191, 41));
        fileNameEdit->setFont(font1);
        fileNameEdit->setFocusPolicy(Qt::ClickFocus);
        fileNameEdit->setStyleSheet(QLatin1String("border: 2px solid rgb(0, 77, 64);\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(0, 150, 136);"));
        recordStartButton = new QPushButton(manualPage);
        recordStartButton->setObjectName(QStringLiteral("recordStartButton"));
        recordStartButton->setGeometry(QRect(380, 45, 101, 41));
        QFont font4;
        font4.setFamily(QStringLiteral("Sans"));
        font4.setPointSize(14);
        recordStartButton->setFont(font4);
        recordStartButton->setFocusPolicy(Qt::NoFocus);
        recordStartButton->setStyleSheet(QLatin1String("QPushButton{background-color: rgba(38, 166, 154,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:pressed{background-color: rgba(0, 77, 64,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}"));
        stackedWidget->addWidget(manualPage);
        autoPage = new QWidget();
        autoPage->setObjectName(QStringLiteral("autoPage"));
        fileNameText = new QLabel(autoPage);
        fileNameText->setObjectName(QStringLiteral("fileNameText"));
        fileNameText->setGeometry(QRect(160, 45, 191, 41));
        fileNameText->setFont(font1);
        fileNameText->setStyleSheet(QLatin1String("border: 2px solid rgb(0, 77, 64);\n"
"background-color: rgb(0, 150, 136);\n"
""));
        label_4 = new QLabel(autoPage);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(40, 50, 101, 31));
        label_4->setFont(font1);
        dispalyWidget_2 = new QWidget(autoPage);
        dispalyWidget_2->setObjectName(QStringLiteral("dispalyWidget_2"));
        dispalyWidget_2->setGeometry(QRect(520, 10, 431, 171));
        dispalyWidget_2->setStyleSheet(QLatin1String("#dispalyWidget_2{background-color: rgb(84, 110, 122);\n"
"border: 2px solid rgb(0, 77, 64);\n"
"border-radius:10px;}"));
        label_44 = new QLabel(dispalyWidget_2);
        label_44->setObjectName(QStringLiteral("label_44"));
        label_44->setGeometry(QRect(20, 60, 61, 31));
        label_44->setFont(font1);
        label_44->setStyleSheet(QLatin1String("background-color: rgb(84, 110, 122);\n"
"color: rgb(255, 255, 255);"));
        label_43 = new QLabel(dispalyWidget_2);
        label_43->setObjectName(QStringLiteral("label_43"));
        label_43->setGeometry(QRect(20, 120, 61, 31));
        label_43->setFont(font1);
        label_43->setStyleSheet(QLatin1String("background-color: rgb(84, 110, 122);\n"
"color: rgb(255, 255, 255);"));
        displayTempLabel_2 = new QLabel(dispalyWidget_2);
        displayTempLabel_2->setObjectName(QStringLiteral("displayTempLabel_2"));
        displayTempLabel_2->setGeometry(QRect(80, 60, 61, 31));
        displayTempLabel_2->setFont(font1);
        displayTempLabel_2->setStyleSheet(QLatin1String("background-color: rgb(84, 110, 122);\n"
"color: rgb(255, 255, 255);"));
        displayPowerLabel_2 = new QLabel(dispalyWidget_2);
        displayPowerLabel_2->setObjectName(QStringLiteral("displayPowerLabel_2"));
        displayPowerLabel_2->setGeometry(QRect(80, 120, 61, 31));
        displayPowerLabel_2->setFont(font1);
        displayPowerLabel_2->setStyleSheet(QLatin1String("background-color: rgb(84, 110, 122);\n"
"color: rgb(255, 255, 255);"));
        label_46 = new QLabel(dispalyWidget_2);
        label_46->setObjectName(QStringLiteral("label_46"));
        label_46->setGeometry(QRect(150, 60, 31, 31));
        label_46->setFont(font1);
        label_46->setStyleSheet(QLatin1String("background-color: rgb(84, 110, 122);\n"
"color: rgb(255, 255, 255);"));
        label_47 = new QLabel(dispalyWidget_2);
        label_47->setObjectName(QStringLiteral("label_47"));
        label_47->setGeometry(QRect(140, 120, 61, 31));
        label_47->setFont(font1);
        label_47->setStyleSheet(QLatin1String("background-color: rgb(84, 110, 122);\n"
"color: rgb(255, 255, 255);"));
        label_48 = new QLabel(dispalyWidget_2);
        label_48->setObjectName(QStringLiteral("label_48"));
        label_48->setGeometry(QRect(210, 60, 121, 31));
        label_48->setFont(font1);
        label_48->setStyleSheet(QLatin1String("background-color: rgb(84, 110, 122);\n"
"color: rgb(255, 255, 255);"));
        label_49 = new QLabel(dispalyWidget_2);
        label_49->setObjectName(QStringLiteral("label_49"));
        label_49->setGeometry(QRect(210, 120, 121, 31));
        label_49->setFont(font1);
        label_49->setStyleSheet(QLatin1String("background-color: rgb(84, 110, 122);\n"
"color: rgb(255, 255, 255);"));
        displayWarningLabel_2 = new QLabel(dispalyWidget_2);
        displayWarningLabel_2->setObjectName(QStringLiteral("displayWarningLabel_2"));
        displayWarningLabel_2->setGeometry(QRect(330, 60, 81, 31));
        displayWarningLabel_2->setFont(font1);
        displayWarningLabel_2->setStyleSheet(QLatin1String("background-color: rgb(84, 110, 122);\n"
"color: rgb(255, 255, 255);"));
        displayControlLabel_2 = new QLabel(dispalyWidget_2);
        displayControlLabel_2->setObjectName(QStringLiteral("displayControlLabel_2"));
        displayControlLabel_2->setGeometry(QRect(330, 120, 81, 31));
        displayControlLabel_2->setFont(font1);
        displayControlLabel_2->setStyleSheet(QLatin1String("background-color: rgb(84, 110, 122);\n"
"color: rgb(255, 255, 255);"));
        label_52 = new QLabel(dispalyWidget_2);
        label_52->setObjectName(QStringLiteral("label_52"));
        label_52->setGeometry(QRect(160, 10, 121, 31));
        label_52->setFont(font1);
        label_52->setStyleSheet(QLatin1String("background-color: rgb(84, 110, 122);\n"
"color: rgb(139, 195, 74);"));
        groupBox_2 = new QGroupBox(autoPage);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(30, 200, 921, 381));
        groupBox_2->setFont(font1);
        groupBox_2->setStyleSheet(QLatin1String("QGroupBox {\n"
"background-color: qlineargradient(spread:pad, x1:0.489, y1:1, x2:0.505682, y2:0.17, stop:0 rgba(128, 203, 196, 255), stop:1 rgba(255, 255, 255, 255));\n"
"    border: 2px solid rgb(0, 77, 64);\n"
"    border-radius: 10px;\n"
"    margin-top: 1em;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 10px;\n"
"    padding: 0 3px 0 3px;\n"
"}"));
        groupBox_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        autoStartButton = new QPushButton(groupBox_2);
        autoStartButton->setObjectName(QStringLiteral("autoStartButton"));
        autoStartButton->setGeometry(QRect(30, 50, 111, 91));
        autoStartButton->setFont(font);
        autoStartButton->setFocusPolicy(Qt::NoFocus);
        autoStartButton->setStyleSheet(QLatin1String("QPushButton{background-color: rgba(38, 166, 154,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:disabled{background-color: rgba(84, 110, 122,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:pressed{background-color: rgba(0, 77, 64,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}"));
        autoListView = new QListView(groupBox_2);
        autoListView->setObjectName(QStringLiteral("autoListView"));
        autoListView->setGeometry(QRect(200, 50, 281, 241));
        QFont font5;
        font5.setPointSize(14);
        autoListView->setFont(font5);
        autoStageTimeText = new QLabel(groupBox_2);
        autoStageTimeText->setObjectName(QStringLiteral("autoStageTimeText"));
        autoStageTimeText->setGeometry(QRect(530, 130, 151, 41));
        autoStageTimeText->setFont(font1);
        autoStageTimeText->setStyleSheet(QLatin1String("background-color: rgb(84, 110, 122);\n"
"color: rgb(255, 255, 255);"));
        autoStageText = new QLabel(groupBox_2);
        autoStageText->setObjectName(QStringLiteral("autoStageText"));
        autoStageText->setGeometry(QRect(530, 90, 151, 41));
        autoStageText->setFont(font1);
        autoStageText->setStyleSheet(QLatin1String("background-color: rgb(84, 110, 122);\n"
"color: rgb(255, 255, 255);"));
        autoIndexText = new QLabel(groupBox_2);
        autoIndexText->setObjectName(QStringLiteral("autoIndexText"));
        autoIndexText->setGeometry(QRect(530, 50, 151, 41));
        autoIndexText->setFont(font1);
        autoIndexText->setStyleSheet(QLatin1String("background-color: rgb(84, 110, 122);\n"
"color: rgb(255, 255, 255);"));
        powerSliderLabel_2 = new QLabel(groupBox_2);
        powerSliderLabel_2->setObjectName(QStringLiteral("powerSliderLabel_2"));
        powerSliderLabel_2->setGeometry(QRect(750, 310, 121, 41));
        powerSliderLabel_2->setFont(font2);
        powerSliderLabel_2->setStyleSheet(QLatin1String("border: 2px solid rgb(0, 77, 64);\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(84, 110, 122);\n"
""));
        powerSlider_2 = new QSlider(groupBox_2);
        powerSlider_2->setObjectName(QStringLiteral("powerSlider_2"));
        powerSlider_2->setGeometry(QRect(150, 310, 581, 41));
        powerSlider_2->setFocusPolicy(Qt::TabFocus);
        powerSlider_2->setStyleSheet(QLatin1String("QSlider{\n"
"background-color: rgba(255, 255, 255, 0);\n"
"}\n"
"QSlider::groove:horizontal { \n"
"height: 20px; \n"
"background: rgb(150, 150, 136); \n"
"margin: 2px 0; \n"
"} \n"
"QSlider::handle:horizontal { \n"
"background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #b4b4b4, stop:1 #8f8f8f); \n"
"border: 1px solid #5c5c5c; \n"
"width: 30px; \n"
"margin: -8px 0px; \n"
"} "));
        powerSlider_2->setOrientation(Qt::Horizontal);
        label_18 = new QLabel(groupBox_2);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(40, 310, 101, 41));
        label_18->setFont(font1);
        label_18->setStyleSheet(QStringLiteral("background-color: rgba(255, 255, 255, 0);"));
        openFileButton = new QPushButton(autoPage);
        openFileButton->setObjectName(QStringLiteral("openFileButton"));
        openFileButton->setGeometry(QRect(380, 45, 101, 41));
        openFileButton->setFont(font4);
        openFileButton->setFocusPolicy(Qt::NoFocus);
        openFileButton->setStyleSheet(QLatin1String("QPushButton{background-color: rgba(38, 166, 154,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:pressed{background-color: rgba(0, 77, 64,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}"));
        stackedWidget->addWidget(autoPage);
        infoPage = new QWidget();
        infoPage->setObjectName(QStringLiteral("infoPage"));
        softVersionLabel = new QLabel(infoPage);
        softVersionLabel->setObjectName(QStringLiteral("softVersionLabel"));
        softVersionLabel->setGeometry(QRect(230, 50, 291, 41));
        softVersionLabel->setFont(font1);
        softVersionLabel->setStyleSheet(QLatin1String("border: 2px solid rgb(0, 77, 64);\n"
"background-color: rgb(0, 150, 136);\n"
""));
        label_26 = new QLabel(infoPage);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(120, 55, 101, 31));
        label_26->setFont(font1);
        label_27 = new QLabel(infoPage);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(120, 175, 101, 31));
        label_27->setFont(font1);
        label_28 = new QLabel(infoPage);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(230, 170, 291, 41));
        label_28->setFont(font1);
        label_28->setStyleSheet(QLatin1String("border: 2px solid rgb(0, 77, 64);\n"
"background-color: rgb(0, 150, 136);\n"
""));
        softUpdateButton = new QPushButton(infoPage);
        softUpdateButton->setObjectName(QStringLiteral("softUpdateButton"));
        softUpdateButton->setGeometry(QRect(620, 40, 111, 71));
        softUpdateButton->setFont(font3);
        softUpdateButton->setFocusPolicy(Qt::NoFocus);
        softUpdateButton->setStyleSheet(QLatin1String("QPushButton{background-color: rgba(38, 166, 154,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:pressed{background-color: rgba(0, 77, 64,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}"));
        restartButton = new QPushButton(infoPage);
        restartButton->setObjectName(QStringLiteral("restartButton"));
        restartButton->setGeometry(QRect(770, 40, 111, 71));
        restartButton->setFont(font3);
        restartButton->setFocusPolicy(Qt::NoFocus);
        restartButton->setStyleSheet(QLatin1String("QPushButton{background-color: rgba(38, 166, 154,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:pressed{background-color: rgba(0, 77, 64,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}"));
        firmwareUpdateButton = new QPushButton(infoPage);
        firmwareUpdateButton->setObjectName(QStringLiteral("firmwareUpdateButton"));
        firmwareUpdateButton->setGeometry(QRect(620, 150, 111, 71));
        firmwareUpdateButton->setFont(font3);
        firmwareUpdateButton->setFocusPolicy(Qt::NoFocus);
        firmwareUpdateButton->setStyleSheet(QLatin1String("QPushButton{background-color: rgba(38, 166, 154,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}\n"
"QPushButton:pressed{background-color: rgba(0, 77, 64,  255);  border: 1px solid rgb(124, 124, 124); border-radius:5px;}"));
        stackedWidget->addWidget(infoPage);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        setButton->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256", 0));
        manualButton->setText(QApplication::translate("MainWindow", "\346\211\213\345\212\250", 0));
        autoButton->setText(QApplication::translate("MainWindow", "\350\207\252\345\212\250", 0));
        infoButton->setText(QApplication::translate("MainWindow", "\344\277\241\346\201\257", 0));
        label_22->setText(QString());
        label_23->setText(QApplication::translate("MainWindow", "\345\212\240\346\226\231\347\255\211\345\276\205\346\227\266\351\227\264\n"
"", 0));
        label_24->setText(QApplication::translate("MainWindow", "\345\212\240\346\226\231\350\266\205\346\227\266\345\212\250\344\275\234", 0));
        label_25->setText(QString());
        setButton_2->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230", 0));
        setButton_3->setText(QApplication::translate("MainWindow", "\345\217\226\346\266\210", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "\345\267\245\350\211\272\346\265\201\347\250\213", 0));
        label_16->setText(QApplication::translate("MainWindow", "\345\212\237\347\216\207\346\216\247\345\210\266", 0));
        powerSliderLabel->setText(QApplication::translate("MainWindow", "150/150kW", 0));
        manualStartButton->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213", 0));
        label_20->setText(QApplication::translate("MainWindow", "\346\227\266\351\227\264", 0));
        manualactionAButton->setText(QApplication::translate("MainWindow", "\345\212\240\346\226\231", 0));
        manualactionBButton->setText(QApplication::translate("MainWindow", "\345\200\222\345\214\205", 0));
        manualactionCButton->setText(QApplication::translate("MainWindow", "\346\215\236\346\270\243", 0));
        manualactionDButton->setText(QApplication::translate("MainWindow", "\346\220\205\346\213\214", 0));
        label_21->setText(QApplication::translate("MainWindow", "\346\223\215\n"
"\344\275\234", 0));
        timeunitlabel->setText(QApplication::translate("MainWindow", "min", 0));
        manualtimelabel->setText(QString());
        label_3->setText(QApplication::translate("MainWindow", "\344\272\247\345\223\201\345\220\215\347\247\260", 0));
        label_6->setText(QApplication::translate("MainWindow", "\346\270\251\345\272\246:", 0));
        label_7->setText(QApplication::translate("MainWindow", "\345\212\237\347\216\207:", 0));
        displayTempLabel->setText(QString());
        displayPowerLabel->setText(QString());
        label_10->setText(QApplication::translate("MainWindow", "\342\204\203", 0));
        label_11->setText(QApplication::translate("MainWindow", "kW", 0));
        label_12->setText(QApplication::translate("MainWindow", "\346\212\245\350\255\246\347\212\266\346\200\201\357\274\232", 0));
        label_13->setText(QApplication::translate("MainWindow", "\345\200\222\345\214\205\346\216\247\345\210\266\357\274\232", 0));
        displayWarningLabel->setText(QString());
        displayControlLabel->setText(QString());
        label_17->setText(QApplication::translate("MainWindow", "\346\255\243\345\270\270\347\224\237\344\272\247", 0));
        recordStartButton->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\350\256\260\345\275\225", 0));
        fileNameText->setText(QString());
        label_4->setText(QApplication::translate("MainWindow", "\344\272\247\345\223\201\345\220\215\347\247\260", 0));
        label_44->setText(QApplication::translate("MainWindow", "\346\270\251\345\272\246:", 0));
        label_43->setText(QApplication::translate("MainWindow", "\345\212\237\347\216\207:", 0));
        displayTempLabel_2->setText(QString());
        displayPowerLabel_2->setText(QString());
        label_46->setText(QApplication::translate("MainWindow", "\342\204\203", 0));
        label_47->setText(QApplication::translate("MainWindow", "kW", 0));
        label_48->setText(QApplication::translate("MainWindow", "\346\212\245\350\255\246\347\212\266\346\200\201\357\274\232", 0));
        label_49->setText(QApplication::translate("MainWindow", "\345\200\222\345\214\205\346\216\247\345\210\266\357\274\232", 0));
        displayWarningLabel_2->setText(QString());
        displayControlLabel_2->setText(QString());
        label_52->setText(QApplication::translate("MainWindow", "\346\255\243\345\270\270\347\224\237\344\272\247", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\345\267\245\350\211\272\346\265\201\347\250\213", 0));
        autoStartButton->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213", 0));
        autoStageTimeText->setText(QString());
        autoStageText->setText(QString());
        autoIndexText->setText(QString());
        powerSliderLabel_2->setText(QApplication::translate("MainWindow", "150/150kW", 0));
        label_18->setText(QApplication::translate("MainWindow", "\345\212\237\347\216\207\346\216\247\345\210\266", 0));
        openFileButton->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200", 0));
        softVersionLabel->setText(QString());
        label_26->setText(QApplication::translate("MainWindow", "\347\250\213\345\272\217\347\211\210\346\234\254", 0));
        label_27->setText(QApplication::translate("MainWindow", "\345\233\272\344\273\266\347\211\210\346\234\254", 0));
        label_28->setText(QString());
        softUpdateButton->setText(QApplication::translate("MainWindow", "\347\250\213\345\272\217\345\215\207\347\272\247", 0));
        restartButton->setText(QApplication::translate("MainWindow", "\351\207\215\345\220\257", 0));
        firmwareUpdateButton->setText(QApplication::translate("MainWindow", "\345\233\272\344\273\266\345\215\207\347\272\247", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
