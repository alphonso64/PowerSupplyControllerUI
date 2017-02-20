#ifndef RFREADER_H
#define RFREADER_H


#include <QThread>
#include <QTimer>
#include "pcstatus.h"
#include "dpustatus.h"
#include <QFile>
#include <QMutex>
#include "const_define.h"
#include "autostate.h"

class RFReader : public QThread
{
    Q_OBJECT
public:
    RFReader(QObject *parent = 0)
        : QThread(parent)
    {

    }
protected:
    void run();

};
#endif // RFREADER_H
