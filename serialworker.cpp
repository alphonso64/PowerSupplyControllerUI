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
		qDebug()<<"open";
	else
		qDebug()<<"not open";
	
	QByteArray array;
	
	char send[10];
	send[0] = 0x6e;
	send[1] = 0x5a;
	send[2] = 8;
	send[3] = 0;
	
	send[6] = 0;
	send[7] = 0;
	
	while(true){
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
					qDebug()<<" temp_a"<<dpuStatus->temp_a<<" temp_b"<<dpuStatus->temp_b<<" ua"<<dpuStatus->ua<<" ia"<<dpuStatus->ia<<" power"<<dpuStatus->power<<" errorcode"<<dpuStatus->errorcode;
				} 
				array->remove(0,i+len);
				flag = true;
				break;
			}
		}
	}
	return flag;
}
