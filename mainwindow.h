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
#include "recorderworker.h"
#include "parseworker.h"
#include "serialworker.h"
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
    void autoStartClick();
    void recordStartClick(bool);
    void timerOut();
    void display();
    void fileOpen();
    void fileParsed();
    void autoProcess();

private:
    void uiInit();
    void autoProcessDisplay();

signals:
    void recordStatus();

private:
    Ui::MainWindow *ui;
    QButtonGroup *group;
    QButtonGroup *group_manual;
    QTime time;
    QTime autotime;
    QTimer *timer;
    QTimer *displaytimer;
    QTimer *autotimer;

    bool startTimerFlag;
    bool recordFlag;
    bool autoStartFlag;
    PcStatus pcStatus;
    DpuStatus dpuStatus;

    RecorderWorker *recorder;
    ParseWorker *parser;
    SerialWorker *serialWorker;

    AutoState autostate;

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
