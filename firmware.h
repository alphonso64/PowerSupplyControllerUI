#ifndef FIRMWARE_H
#define FIRMWARE_H
#include <QString>
#include "util.h"
class FirmWare
{
public:
    FirmWare(QString path,QString path_);
    ~FirmWare();

    int getSendSize();
    int getFileSize();
    char* getSendTemp();
    int packgeNum();
    void setPackage(int packge,int version);
    void setStart();

private:
    char *fileSrc;
    char *fileSrc_;
    int totalPackage;
    int currenPackge;
    int fileSize;
    char *sendTemp;
    int sendSize;

};

#endif // FIRMWARE_H
