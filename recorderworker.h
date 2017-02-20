#ifndef RECORDERWORKER_H
#define RECORDERWORKER_H

#include <QThread>
#include <QTimer>
#include "pcstatus.h"
#include "dpustatus.h"
#include "json/json.h"
#include <QFile>
#include <QMutex>
class RecorderWorker : public QThread
{
    Q_OBJECT
public:
    RecorderWorker(QObject *parent = 0)
        : QThread(parent)
    {

    }
protected:
    void run();
private slots:
    void timeOut();
    void actionRecord();
    void actionRecord(QString content);

public:
    QTimer *timer;
    PcStatus *pcStatus;
    DpuStatus *dpuStatus;
    QMutex m_lock;
    QString fileName;
signals:
    void fileRecorded();
private:
    Json::Value *root;

};

#endif // RECORDERWORKER_H
