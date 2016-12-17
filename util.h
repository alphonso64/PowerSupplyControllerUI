#ifndef UTIL_H
#define UTIL_H
#include <QStringList>
#include <libserialport.h>
#include <stdio.h>
#include "serial/serial.h"
using std::vector;
class Util
{
public:
    Util();

    static QStringList getLocalFileList();
    static QString readFile(QString path);
	static void list_ports()
	{
		vector<serial::PortInfo> devices_found = serial::list_ports();

		vector<serial::PortInfo>::iterator iter = devices_found.begin();

		while( iter != devices_found.end() )
		{
			serial::PortInfo device = *iter++;

			printf( "(%s, %s, %s)\n", device.port.c_str(), device.description.c_str(),
		 device.hardware_id.c_str() );
		}
	}


};

#endif // UTIL_H
