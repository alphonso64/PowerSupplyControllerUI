#include "filecopyer.h"

void FileCopyer::run()
{
    QString dst(UPDATE_TEMP_PATH);
    Util::cpyFile(filename.toStdString().c_str(),dst.toStdString().c_str());
    Util::fileSync(dst.toStdString().c_str());
    cusDiliag->changeStyle(UPDATE_END,1);
}
