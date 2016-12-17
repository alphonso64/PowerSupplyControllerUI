#ifndef SERIALWORKER_H
#define SERIALWORKER_H
#include <QThread>
#include "dpustatus.h"
#include "pcstatus.h"
class SerialWorker : public QThread
{
    Q_OBJECT
public:
    SerialWorker(QObject *parent = 0)
        : QThread(parent)
    {

    }
	DpuStatus *dpuStatus;
	PcStatus *pcStatus;
protected:
    void run();
private:
    bool dataParse(QByteArray *array,DpuStatus *dpuStatus);
};
#endif // SERIALWORKER_H
