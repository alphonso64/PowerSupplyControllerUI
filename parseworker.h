#ifndef PARSEWORKER_H
#define PARSEWORKER_H
#include <QThread>
#include <QTimer>
#include "pcstatus.h"
#include "dpustatus.h"
#include "json/json.h"
#include <QFile>
#include <QMutex>
#include "const_define.h"
#include "autostate.h"

class ParseWorker : public QThread
{
    Q_OBJECT
public:
    ParseWorker(QObject *parent = 0)
        : QThread(parent)
    {

    }
protected:
    void run();

signals:
    void parsed();

public:
    QString fileName;
    AutoState autostate;
};

#endif // PARSEWORKER_H
