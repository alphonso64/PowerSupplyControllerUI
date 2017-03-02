#include "actiondialog.h"
#include "ui_actiondialog.h"
#include <QStringListModel>
#include "util.h"
#include <QDebug>
#include "const_define.h"
#include <QMapIterator>
ActionDialog::ActionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ActionDialog)
{
    ui->setupUi(this);


    this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint |Qt::X11BypassWindowManagerHint);
    this->move(192,144);
    fileName = "";
    filePath = "";

    connect(ui->doneButton, SIGNAL(clicked()),this, SLOT(doneExit()));
    connect(ui->rejectButton, SIGNAL(clicked()),this, SLOT(rejectExit()));
}

void ActionDialog::setStyle(int style)
{
    if(style == 0)
    {
        QStringListModel *model = new QStringListModel(this);
        model->setStringList( Util::getLocalFileList());
        ui->listView->setModel(model);
        ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }else{
        QMapIterator<QString, QString> i(list);
        QStringList stringList;
        while (i.hasNext()) {
          stringList.append(i.next().key());
        }
        QStringListModel *model = new QStringListModel(this);
        model->setStringList( stringList);
        ui->listView->setModel(model);
        ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}

void ActionDialog::rejectExit()
{
    done(-1);
}

void ActionDialog::doneExit()
{
    QModelIndexList list =ui->listView->selectionModel()->selectedIndexes();
    if(list.size()>0)
    {
        qDebug() << list.at(0).data(Qt::DisplayRole ).toString();
        fileName = list.at(0).data(Qt::DisplayRole ).toString();
        filePath = PrePath + fileName;
    }else{
        fileName = "";
        filePath = "";
    }
    done(0);
}

ActionDialog::~ActionDialog()
{
    delete ui;
}
