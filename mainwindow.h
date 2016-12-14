#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include "const_define.h"
#include <QTime>
#include <QTimer>
#include "cusdialog.h"
#include "pcstatus.h"
#include "dpustatus.h"

#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



private slots:
    void groupButtonClick(int);
    void actionGroupButtonClick(int);
    void setPowerValue(int);
    void manualStartClick(bool);
    void recordStartClick(bool);
    void timerOut();
    void display();

private:
    void uiInit();

private:
    Ui::MainWindow *ui;
    QButtonGroup *group;
    QButtonGroup *group_manual;
    QTime time;
    QTimer *timer;
    QTimer *displaytimer;

    bool startTimerFlag;
    bool recordFlag;
    PcStatus pcStatus;
    DpuStatus dpuStatus;

    static const int setBtnID = 1;
    static const int manualBtnID = 2;
    static const int autoBtnID = 3;
    static const int infoBtnID = 4;

    static const int manualAID = 11;
    static const int manualBID = 12;
    static const int manualCID = 13;
    static const int manualDID = 14;
};

#endif // MAINWINDOW_H
