#ifndef SERIALWORKER_H
#define SERIALWORKER_H
#include <QThread>
#include "dpustatus.h"
#include "pcstatus.h"
#include "firmware.h"
#include "cusdialog.h"
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
	QString path_;
    bool updateFirmWareFlag;
	CusDialog *cusdialog;
protected:
    void run();
signals:
    void errorDispatch(int);
private:
    int errorFlag;

    int updateFirmWareState;
    FirmWare *firmWare;
    bool dataParse(QByteArray *array,DpuStatus *dpuStatus);
    bool updateDataParse(QByteArray *array,unsigned int *package,unsigned int *state,unsigned int *version);
    bool checksumValidate(QByteArray *data, int offset,int len, unsigned int checksum);
};
#endif // SERIALWORKER_H
