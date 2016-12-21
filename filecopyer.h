#ifndef FILECOPYER_H
#define FILECOPYER_H

#include <QThread>
#include <QString>
#include "util.h"
#include "cusdialog.h"
#include "const_define.h"

class FileCopyer : public QThread
{
    Q_OBJECT
public:
    FileCopyer(QObject *parent = 0)
        : QThread(parent)
    {

    }
    CusDialog *cusDiliag;
    QString filename;
protected:
    void run();



};
#endif // FILECOPYER_H
