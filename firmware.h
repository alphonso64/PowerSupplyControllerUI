#ifndef FIRMWARE_H
#define FIRMWARE_H
#include <QString>
#include "util.h"
class FirmWare
{
public:
    FirmWare(QString path);
    ~FirmWare();

    int getSendSize();
    int getFileSize();
    char* getSendTemp();
    int packgeNum();
    void setPackage(int packge);
    void setStart();

private:
    char *fileSrc;
    int totalPackage;
    int currenPackge;
    int fileSize;
    char *sendTemp;
    int sendSize;

};

#endif // FIRMWARE_H
