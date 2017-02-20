#include "mainwindow.h"
#include <QApplication>
#include <frminput.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    frmInput::Instance()->Init("control", "black", 10, 10);
    //a.setOverrideCursor(Qt::BlankCursor);
    return a.exec();
}
