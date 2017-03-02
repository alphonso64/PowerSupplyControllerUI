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
#include "errorpage.h"
#include "filecopyer.h"
#include "rfreader.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QMutex>
#include "adddialog.h"
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
    void actionGroupButtonClick(int);
    void setPowerValue(int);
    void manualStartClick(bool);
    void autoStartClick();
    void recordStartClick(bool);
    void timerOut();
    void acctimerOut();
    void display();
    void fileOpen();
    void fileParsed();
    void autoProcess();
    void fileRecorded();
    void setButtonClick();
    void manualButtonClick();
    void autoButtonClick();
    void infoButtonClick();
    void errorHandle(int);
    void errorDismissHandle(int);
    void softUpdateButtonClick();
    void restartButtonClick();
    void firmwarepdateButtonClick();
    void stateUpload();
    void fileUpload();
    void fileDownload();
    void netfinished();
    void fileUploadfinished();
    void fileListDownloadinished();
    void fileDownloadinished();
    void manualAdd();
    void manualMinus();

private:
    void uiInit();
    void autoProcessDisplay();

signals:
    void recordStatus();
    void recordStatus(QString content);

private:
    Ui::MainWindow *ui;
    QButtonGroup *group_manual;
    QTime time;
    QTime acctime;
    QTime autotime;
    QTimer *timer;
    QTimer *displaytimer;
    QTimer *autotimer;
    QTimer *nettimer;
    QTimer *acctimer;

    QNetworkAccessManager *nam;

    bool startTimerFlag;
    bool recordFlag;
    bool autoStartFlag;
    bool netStateFlag;
    bool netStartFlag;
    PcStatus pcStatus;
    DpuStatus dpuStatus;

    RecorderWorker *recorder;
    ParseWorker *parser;
    SerialWorker *serialWorker;
    FileCopyer *copyer;
    RFReader *rfreader;

    AutoState autostate;
    ErrorPage *errorPage;

    int auto_index;
    CusDialog *auto_CusDialog;
    CusDialog *warn_CusDialog;
    CusDialog *fileupload_CusDialog;

    QNetworkReply *state_reply;
    QNetworkReply *file_reply;
    QNetworkReply *file_down_reply;
    QString downFileName;
    QMutex mutex;

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
