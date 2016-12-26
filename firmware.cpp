#include "firmware.h"
#include <QDebug>
#define PACKGE_SIZE 512

FirmWare::FirmWare(QString path,QString path_)
{
    sendTemp = new char[1024];
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
    fread (fileSrc,1,fileSize,fp) ;
    fclose(fp);

    fp = fopen(path_.toStdString().c_str(), "rb+");
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
    fileSrc_ = new char[fileSize];
    fread (fileSrc_,1,fileSize,fp) ;
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

void FirmWare::setPackage(int packge,int version)
{
    currenPackge = packge;
    int size = 0;
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
    if(version == 0){
        memcpy(sendTemp+10, fileSrc + currenPackge * PACKGE_SIZE, size);
    }else if(version == 1){
        memcpy(sendTemp+10, fileSrc_ + currenPackge * PACKGE_SIZE, size);
    }
	//memcpy(sendTemp+10, fileSrc + currenPackge * PACKGE_SIZE, size);	
    int offset = 10+size;
    unsigned int checksum = 0;
    for(int i=4;i<offset;i++)
    {
        checksum = checksum + ((uint8_t)sendTemp[i]);
    }
	// qDebug()<<"packge"<<packge<<""<<"size"<<size;
    sendTemp[offset] = checksum & 0xff;
    sendTemp[offset+1] = (checksum>>8) & 0xff;
    sendTemp[offset+2] = (checksum>>16) & 0xff;
    sendTemp[offset+3] = (checksum>>24) & 0xff;

    sendSize = size+14;
}

void FirmWare::setStart()
{
    sendTemp[0] = 0x68;
    sendTemp[1] = 0x5a;
    sendTemp[2] = 0x0C;
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


    unsigned int checksum = 0;
    for(int i=0;i<16;i++)
    {
        checksum = checksum + ((uint8_t)sendTemp[i]);
    }
    sendTemp[16] = checksum & 0xff;
    sendTemp[17] = (checksum>>8) & 0xff;
    sendTemp[18] = (checksum>>16) & 0xff;
    sendTemp[19] = (checksum>>24) & 0xff;
    sendSize = 20;
	// qDebug()<<"totalPackage"<<totalPackage;

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
    if(fileSrc_ != NULL){
        delete fileSrc_;
        fileSrc_ = NULL;
    }
}
