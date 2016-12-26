#ifndef UTIL_H
#define UTIL_H
#include <QStringList>
#include <stdio.h>
#include "serial/serial.h"
using std::vector;
class Util
{
public:
    Util();

    static QStringList getLocalFileList();
    static QString readFile(QString path);
    static void fileSync(const char *file);
    static int get_file_size(FILE *file);
    static void cpyFile(const char *src,const char *dst);
    static void list_ports();
    static QString checkUDiskPath();
    static QString checkUpdatePath(QString udiskPath);
    static QString checkFirmWareUpdatePath(QString udiskPath);
	static QString checkFirmWareUpdatePath_(QString udiskPath);
	static void deleteUnpluedUdiskPath();

};

#endif // UTIL_H
