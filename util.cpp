#include "util.h"
#include <QSettings>
#include <stdio.h>
#include <QRegExp>
#include <QDebug>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include "const_define.h"
#include <sys/stat.h>
#include <map>
#include <QDateTime>
#include <fcntl.h>
#include <const_define.h>
#include <QDir>
#include <sys/sendfile.h>
typedef std::multimap<time_t, std::string> result_set_t;

Util::Util()
{
}

void Util::list_ports()
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

QStringList Util::getLocalFileList()
{

    QDir dir(PrePath);
    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Time);
    QStringList filelist;
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        filelist.push_back(fileInfo.fileName());
    }
    return filelist;
}

QString Util::readFile(QString path)
{
    QFile f(path);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return NULL;
    }

    QTextStream input(&f);
    return input.readAll();
}

void Util::fileSync(const char *file)
{
    int fd =  open( file, O_RDWR);
    if(fd != -1)
    {
        syncfs(fd);
        close(fd);
    }
}

int Util::get_file_size(FILE *file)
{
    int size = 0;
    fseek(file, 0L, SEEK_END);
    size = ftell(file);
    fseek(file, 0L, SEEK_SET);
    return size;
}

void Util::cpyFile(const char *src, const char *dst)
{
	 int read_fd;
	 int write_fd;
	 struct stat stat_buf;
	 off_t offset = 0;

	 /* Open the input file. */
	 read_fd = open (src, O_RDONLY);
	 /* Stat the input file to obtain its size. */
	 fstat (read_fd, &stat_buf);
	 /* Open the output file for writing, with the same permissions as the
	   source file. */
	 write_fd = open (dst, O_WRONLY | O_CREAT, stat_buf.st_mode);
	 /* Blast the bytes from one file to the other. */
	 sendfile (write_fd, read_fd, &offset, stat_buf.st_size);
	 /* Close up. */
	 close (read_fd);
	 close (write_fd);
	 
	 chmod(dst,S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH|S_IXOTH);
}

QString Util::checkUDiskPath()
{
    DIR    *dir;
    struct    dirent    *ptr;
    dir = opendir(UDISK_PATH_PREFIX); ///open the dir
    QString pattern_a("\\.");
    QString pattern_b("\\.\\.");
    QRegExp rx_a(pattern_a);
    QRegExp rx_b(pattern_b);

    while((ptr = readdir(dir)) != NULL) ///read the list of this dir
    {
        if(ptr->d_type == 4)
        {
            {
                if(!rx_a.exactMatch(ptr->d_name))
                {
                    if(!rx_b.exactMatch(ptr->d_name))
                    {
                        closedir(dir);
                        return QString(ptr->d_name);
                    }
                }
            }
        }
    }
    closedir(dir);
    return NULL;
}

QString Util::checkUpdatePath(QString udiskPath)
{
    DIR    *dir;
    struct    dirent    *ptr;
    dir = opendir(udiskPath.toStdString().c_str()); ///open the dir
    if(dir==NULL){
        return NULL;
    }
    QString pattern("PowerSupplyController");
    QRegExp rx(pattern);

    while((ptr = readdir(dir)) != NULL) ///read the list of this dir
    {
        //if(ptr->d_type == 4)
        {
            qDebug()<<ptr->d_name;
            if(rx.exactMatch(ptr->d_name))
            {
                closedir(dir);
                return QString(ptr->d_name);
            }
        }
    }
    closedir(dir);
    return NULL;
}

QString Util::checkFirmWareUpdatePath(QString udiskPath)
{
    DIR    *dir;
    struct    dirent    *ptr;
    dir = opendir(udiskPath.toStdString().c_str()); ///open the dir
    if(dir==NULL){
        return NULL;
    }
    QString pattern("Robos0.bin");
    QRegExp rx(pattern);

    while((ptr = readdir(dir)) != NULL) ///read the list of this dir
    {
        //if(ptr->d_type == 4)
        {
            qDebug()<<ptr->d_name;
            if(rx.exactMatch(ptr->d_name))
            {
                closedir(dir);
                return QString(ptr->d_name);
            }
        }
    }
    closedir(dir);
    return NULL;
}

void Util::deleteUnpluedUdiskPath()
{
    DIR    *dir;
    struct    dirent    *ptr;
    dir = opendir(UDISK_PATH_PREFIX);
    QString path_pre = QString(UDISK_PATH_PREFIX);
    QString pattern_a("\\.");
    QString pattern_b("\\.\\.");
    QRegExp rx_a(pattern_a);
    QRegExp rx_b(pattern_b);
    while((ptr = readdir(dir)) != NULL) ///read the list of this dir
    {
        if(ptr->d_type == 4)
        {

            if(!rx_a.exactMatch(ptr->d_name))
            {
                if(!rx_b.exactMatch(ptr->d_name))
                {
                    QString path = QString(path_pre+ptr->d_name);
                    struct stat buf;
                    int res  = stat(path.toStdString().c_str(), &buf);
                    if(res == 0)
                    {
                        if(buf.st_uid != 1000)
                        {
                            QString cmd("sudo rm -rf "+path_pre+"\""+ptr->d_name+"\"");
                            system(cmd.toStdString().c_str());
                        }
                    }


                }
            }
        }
    }

    closedir(dir);
}

QString Util::checkFirmWareUpdatePath_(QString udiskPath)
{
    DIR    *dir;
    struct    dirent    *ptr;
    dir = opendir(udiskPath.toStdString().c_str()); ///open the dir
    if(dir==NULL){
        return NULL;
    }
    QString pattern("Robos1.bin");
    QRegExp rx(pattern);

    while((ptr = readdir(dir)) != NULL) ///read the list of this dir
    {
        //if(ptr->d_type == 4)
        {
            qDebug()<<ptr->d_name;
            if(rx.exactMatch(ptr->d_name))
            {
                closedir(dir);
                return QString(ptr->d_name);
            }
        }
    }
    closedir(dir);
    return NULL;
}
