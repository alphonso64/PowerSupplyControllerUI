#ifndef SERIALWORKER_H
#define SERIALWORKER_H
#include <QThread>
#include "dpustatus.h"
#include "pcstatus.h"
#include "firmware.h"
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
    QString path;
    bool updateFirmWareFlag;
protected:
    void run();
signals:
    void errorDispatch(int);
private:
    int errorFlag;

    int updateFirmWareState;
    FirmWare *firmWare;
    bool dataParse(QByteArray *array,DpuStatus *dpuStatus);
    bool updateDataParse(QByteArray *array,unsigned int *package,unsigned int *state);
};
#endif // SERIALWORKER_H
