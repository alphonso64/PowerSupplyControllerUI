#include "firmware.h"

#define PACKGE_SIZE 512

FirmWare::FirmWare(QString path)
{

    FILE *fp = fopen(path.toStdString().c_str(), "rb+");
    if(NULL == fp)
    {
        return ;
    }
    fileSize = Util::get_file_size(fp) ;
    if(fileSize == 0)
    {
        return ;
    }
    sendSize = 0;
    totalPackage = fileSize/PACKGE_SIZE + 1;
    currenPackge = 0;
    fileSrc = new char[fileSize];
    sendTemp = new char[1024];
    fread (fileSrc,1,fileSize,fp) ;
    fclose(fp);
}

int FirmWare::getSendSize()
{
    return sendSize;
}

char*  FirmWare::getSendTemp()
{
    return sendTemp;
}

int FirmWare::packgeNum()
{
    return totalPackage;
}

int FirmWare::getFileSize()
{
    return fileSize;
}

void FirmWare::setPackage(int packge)
{
    currenPackge = packge;
    int size;
    if(packge < totalPackage-1)
    {
        size = PACKGE_SIZE;

    }else if(packge == totalPackage - 1)
    {
        size  = fileSize - currenPackge * PACKGE_SIZE;
    }else{
        return;
    }
    sendTemp[0] = 0x6b;
    sendTemp[1] = 0x5a;
    sendTemp[2] = size&0xff;
    sendTemp[3] = (size>>8)&0xff;
    sendTemp[4] = 0;
    sendTemp[5] = 0;
    sendTemp[6] = currenPackge & 0xff;
    sendTemp[7] = (currenPackge>>8) & 0xff;
    sendTemp[8] = (currenPackge>>16) & 0xff;
    sendTemp[9] = (currenPackge>>24) & 0xff;
    memcpy(sendTemp+10, fileSrc + currenPackge * PACKGE_SIZE, size);
    int offset = 10+size;
    sendTemp[offset] = 0xff;
    sendTemp[offset+1] = 0xff;
    sendTemp[offset+2] = 0xff;
    sendTemp[offset+3] = 0xff;
    sendSize = size+14;
}

void FirmWare::setStart()
{
    sendTemp[0] = 0x68;
    sendTemp[1] = 0x5a;
    sendTemp[2] = 0x10;
    sendTemp[3] = 0;


    sendTemp[4] = fileSize & 0xff;
    sendTemp[5] = (fileSize>>8) & 0xff;
    sendTemp[6] = (fileSize>>16) & 0xff;
    sendTemp[7] = (fileSize>>24) & 0xff;

    sendTemp[8] = totalPackage & 0xff;
    sendTemp[9] = (totalPackage>>8) & 0xff;
    sendTemp[10] = (totalPackage>>16) & 0xff;
    sendTemp[11] = (totalPackage>>24) & 0xff;

    sendTemp[12] = 0;
    sendTemp[13] = 0;
    sendTemp[14] = 0;
    sendTemp[15] = 0;

    sendTemp[16] = 0;
    sendTemp[17] = 0;
    sendTemp[18] = 0;
    sendTemp[19] = 0;

    sendTemp[20] = 0xff;
    sendTemp[21] = 0xff;
    sendTemp[22] = 0xff;
    sendTemp[23] = 0xff;
    sendSize = 24;

}

FirmWare::~FirmWare()
{
    if(sendTemp != NULL){
        delete sendTemp;
        sendTemp = NULL;
    }
    if(fileSrc != NULL){
        delete fileSrc;
        fileSrc = NULL;
    }
}
