#include "serialworker.h"
#include <QDebug>
#include "util.h"
#include "serial/serial.h"
//#include "libserialport.h"
#include <QByteArray>
void SerialWorker::run()
{
	Util::list_ports();
    serial::Serial my_serial(COM6, 115200, serial::Timeout::simpleTimeout(2000));
    //serial::Serial my_serial("/dev/ttyS0", 115200, serial::Timeout::simpleTimeout(2000));
	if(my_serial.isOpen())
        qDebug()<<"has open";
	else
		qDebug()<<"not open";
	
	QByteArray array;
    errorFlag = 0;
	
	char send[10];
	send[0] = 0x6e;
	send[1] = 0x5a;
	send[2] = 8;
	send[3] = 0;
	
	send[6] = 0;
	send[7] = 0;

    updateFirmWareFlag =false;
    updateFirmWareState =0;
	
	while(true){

        if(updateFirmWareFlag)
        {
            if(updateFirmWareState == 0)
            {
				my_serial.flushOutput();
                sleep(2);
                if(firmWare!=NULL){
                    delete firmWare;
                }
                firmWare = new FirmWare(path,path_);
				qDebug()<<path<<path_;
                firmWare->setStart();
                qDebug()<<"setStart"<<firmWare->getSendSize()<<" "<<firmWare->getFileSize();
                my_serial.write((uint8_t *)firmWare->getSendTemp(),firmWare->getSendSize());
                updateFirmWareState = 1;
            }else
            {
                char  temp[16];
                int bytes_wrote = my_serial.read((uint8_t *)temp,16);
                QByteArray val((char *)temp,bytes_wrote);
                array.append(val);
                unsigned int state = 0;
                unsigned int package =  0;
                unsigned int version =  0;
                while(updateDataParse(&array,&package,&state,&version)){
                }
                if(state == 1){
					firmWare->setPackage(package,version);
                    qDebug()<<"updateDataParse "<<package<<" size "<<firmWare->getSendSize()<<" version"<<version;
                    my_serial.write((uint8_t *)firmWare->getSendTemp(),firmWare->getSendSize());
                }else if(state == 2){
					qDebug()<<"update done";
					updateFirmWareFlag = false;
					updateFirmWareState =0;
					cusdialog->changeStyle(UPDATE_END,1);
				}

            }
        }else
        {
            char  temp[20];
            int bytes_wrote = my_serial.read((uint8_t *)temp,20);
            QByteArray val((char *)temp,bytes_wrote);

            array.append(val);
            while(dataParse(&array,dpuStatus)){

            }
            send[4] = pcStatus->powerlevel &0xff;
            send[5] = (pcStatus->powerlevel>>8)&0xff;

            if(pcStatus->warningControl){
                send[6] = 1;
            }else{
                send[6] = 0;
            }

            if(pcStatus->toppleControl){
                send[7] = 1;
            }else{
                send[7] = 0;
            }
            my_serial.write((uint8_t *)send,8);
        }
	}
	my_serial.close();
}

bool SerialWorker::dataParse(QByteArray *array,DpuStatus *dpuStatus)
{
	bool flag = false;
	for(int i=0;i<array->length()-3;i++)
	{
		if(array->at(i) == 0x6c && array->at(i+1) == 0x5a)
		{
			int len = (array->at(i+3)<<8) + array->at(i+2) + 4;
			if((len + i) > array->length())
			{
				break;
			}else{
				{
					dpuStatus->temp_a =	(((uint8_t)array->at(i+5)<<8) + (uint8_t)array->at(i+4))/100;
					dpuStatus->temp_b =	(((uint8_t)array->at(i+7)<<8) + (uint8_t)array->at(i+6))/100;
					dpuStatus->ua =	(((uint8_t)array->at(i+9)<<8) + (uint8_t)array->at(i+8))/100;
					dpuStatus->ia =	(((uint8_t)array->at(i+11)<<8) + (uint8_t)array->at(i+10))/100;
					dpuStatus->power = (((uint8_t)array->at(i+15)<<24)+ ((uint8_t)array->at(i+14)<<16) + ((uint8_t)array->at(i+13)<<8) + (uint8_t)array->at(i+12))/100;
					dpuStatus->errorcode = ((uint8_t)array->at(i+19)<<24)+ ((uint8_t)array->at(i+18)<<16) + ((uint8_t)array->at(i+17)<<8) + (uint8_t)array->at(i+16);
                    if(dpuStatus->errorcode&0x1!=0){
                        if(errorFlag == 0){
                            qDebug()<<"errorDispatch(1)";
                            emit(errorDispatch(1));
                            errorFlag = 1;
                        }
                    }else{
                        if(errorFlag!=0){
                            qDebug()<<"errorDispatch(0)";
                            emit(errorDispatch(0));
                            errorFlag = 0;
                        }
                    }
				} 
				array->remove(0,i+len);
				flag = true;
				break;
			}
		}
	}
	return flag;
}

bool SerialWorker::updateDataParse(QByteArray *array,unsigned int *package,unsigned int *state,unsigned int *version)
{
    bool flag = false;
    for(int i=0;i<array->length()-4;i++)
    {
        if(array->at(i) == 0x6a && array->at(i+1) == 0x5a)
        {
            int datelen = (array->at(i+3)<<8) + array->at(i+2);
            int len = datelen + 8;
            if((len + i) > array->length())
            {
                break;
            }else{
                unsigned int checksum = ((uint8_t)array->at(datelen+7)<<24)+ ((uint8_t)array->at(datelen+6)<<16) + ((uint8_t)array->at(datelen+5)<<8) + (uint8_t)array->at(datelen+4);
				
                if(checksumValidate(array,0,datelen+4,checksum))
				{
                    *state = ((uint8_t)array->at(i+5)<<8) + (uint8_t)array->at(i+4);
                    *version = ((uint8_t)array->at(i+7)<<8) + (uint8_t)array->at(i+6);
                    *package = ((uint8_t)array->at(i+11)<<24)+ ((uint8_t)array->at(i+10)<<16) + ((uint8_t)array->at(i+9)<<8) + (uint8_t)array->at(i+8);
                    array->remove(0,i+len);
                    flag = true;
                    break;
                }
				array->remove(0,i+len);
            }
        }
    }
    return flag;
}

bool SerialWorker::checksumValidate(QByteArray *data, int offset,int len, unsigned int checksum)
{
    bool flag = false;
    unsigned int sum = 0;
    for(int i=0;i<len;i++){
        sum = sum + (uint8_t(data->at(i+offset)));
    }
	//qDebug()<<"sum"<<sum<<" checksum"<<checksum;
    if(sum == checksum)
        flag = true;
    return flag;
}
