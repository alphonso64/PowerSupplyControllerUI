#include "serialworker.h"
#include <QDebug>
#include "util.h"
#include "serial/serial.h"
//#include "libserialport.h"
#include <QByteArray>
void SerialWorker::run()
{
	Util::list_ports();
	serial::Serial my_serial("/dev/ttyS0", 115200, serial::Timeout::simpleTimeout(2000));
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
                sleep(0.5);
                if(firmWare!=NULL){
                    delete firmWare;
                }
                firmWare = new FirmWare(path);
                firmWare->setStart();
                qDebug()<<"setStart"<<firmWare->getSendSize()<<" "<<firmWare->getFileSize();
                my_serial.write((uint8_t *)firmWare->getSendTemp(),firmWare->getSendSize());
                updateFirmWareState = 1;
            }else
            {
                char  temp[14];
                int bytes_wrote = my_serial.read((uint8_t *)temp,14);
                QByteArray val((char *)temp,bytes_wrote);
                array.append(val);
                unsigned int state = 0;
                unsigned int package =  0;
                while(updateDataParse(&array,&package,&state)){
                }
//				qDebug()<<"updateDataParse "<<package<<"state "<<state;
                if(state == 1){
					qDebug()<<"updateDataParse "<<package<<"size "<<firmWare->getSendSize();
                    firmWare->setPackage(package);
                    my_serial.write((uint8_t *)firmWare->getSendTemp(),firmWare->getSendSize());
                }else if(state == 2){
					qDebug()<<"update done";
					updateFirmWareFlag = false;
					updateFirmWareState =0;
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

bool SerialWorker::updateDataParse(QByteArray *array,unsigned int *package,unsigned int *state)
{
    bool flag = false;
    for(int i=0;i<array->length()-4;i++)
    {
        if(array->at(i) == 0x6a && array->at(i+1) == 0x5a)
        {
            int len = (array->at(i+3)<<8) + array->at(i+2) + 8;
            if((len + i) > array->length())
            {
                break;
            }else{
                *state = ((uint8_t)array->at(i+5)<<8) + (uint8_t)array->at(i+4);
                *package = ((uint8_t)array->at(i+9)<<24)+ ((uint8_t)array->at(i+8)<<16) + ((uint8_t)array->at(i+7)<<8) + (uint8_t)array->at(i+6);
                array->remove(0,i+len);
                flag = true;
                break;
            }
        }
    }
    return flag;
}
