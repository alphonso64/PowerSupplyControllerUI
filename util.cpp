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
typedef std::multimap<time_t, std::string> result_set_t;

Util::Util()
{
}

QStringList Util::getLocalFileList()
{
//    QStringList list;
//    DIR    *dir;
//    struct    dirent    *ptr;
//    dir = opendir(PrePath.toStdString().c_str()); ///open the dir
//    result_set_t res_set;
//    while((ptr = readdir(dir)) != NULL) ///read the list of this dir
//    {
//        std::string name(ptr->d_name);
//        std::string path = QString(PrePath+name.c_str()).toStdString();
//        struct stat buf;
//        stat(path.c_str(), &buf);
//        if(buf.st_size>0)
//        {
//            res_set.insert(result_set_t::value_type(buf.st_mtime,name));
//        }
//    }
//    std::multimap<time_t, std::string>::reverse_iterator   i, iend;
//    iend = res_set.rend();
//    for (i=res_set.rbegin(); i!=iend; ++i)
//    {
//        list.push_back(((std::string)((*i).second)).c_str());
//    }
//    closedir(dir);
//    return list;

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
