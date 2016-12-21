#include "recorderworker.h"
#include <QDebug>

//int cnt;

void RecorderWorker::run()
{

//    cnt = 0;
    root = new Json::Value();
//    qDebug()<<this->currentThreadId()<< " RecorderWorker thread start";
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(timeOut()),Qt::DirectConnection);
    timer->start(1000);
    exec();

    timer->stop();
    Json::FastWriter writer;

    m_lock.lock();

    std::string strWrite = writer.write(*root);
    QFile data(PrePath+fileName);
    if (data.open(QFile::WriteOnly | QIODevice::Truncate)) {
        QTextStream out(&data);
        out << QString(strWrite.c_str());
    }

    delete root;
    delete timer;
    m_lock.unlock();
    emit(fileRecorded());
//    qDebug()<<this->currentThreadId() << " exit";
}

void RecorderWorker::actionRecord()
{
    qDebug()<<"actionRecord";
    m_lock.lock();
    Json::Value content;
//    content["index"] = cnt++;
    content["level"] = pcStatus->powerlevel;
    content["power"] = dpuStatus->power;
    content["temp"] = dpuStatus->temp_a;
    content["action"] = pcStatus->action;
    content["ac_sta"] = pcStatus->actionState;
    content["ac_info"] = pcStatus->actionInfo.toStdString();
    root->append(content);
    m_lock.unlock();
}

void RecorderWorker::timeOut()
{
    m_lock.lock();
    Json::Value content;
//    content["index"] = cnt++;
    content["level"] = pcStatus->powerlevel;
    content["power"] = dpuStatus->power;
    content["temp"] = dpuStatus->temp_a;
    content["action"] = pcStatus->action;
    content["ac_sta"] = pcStatus->actionState;
    content["ac_info"] = pcStatus->actionInfo.toStdString();
    root->append(content);
    m_lock.unlock();
}
