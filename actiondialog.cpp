#include "actiondialog.h"
#include "ui_actiondialog.h"
#include <QStringListModel>
#include "util.h"
#include <QDebug>
#include "const_define.h"
ActionDialog::ActionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ActionDialog)
{
    ui->setupUi(this);
    QStringListModel *model = new QStringListModel(this);
    model->setStringList( Util::getLocalFileList());
    ui->listView->setModel(model);

    fileName = "";
    filePath = "";

    connect(ui->doneButton, SIGNAL(clicked()),this, SLOT(doneExit()));
    connect(ui->rejectButton, SIGNAL(clicked()),this, SLOT(rejectExit()));
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
