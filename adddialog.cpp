#include "adddialog.h"
#include "ui_adddialog.h"
#include <QStringListModel>
#include <QDebug>
AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint |Qt::X11BypassWindowManagerHint);
    this->move(192,144);
    connect(ui->doneButton, SIGNAL(clicked()),this, SLOT(doneExit()));
    connect(ui->rejectButton, SIGNAL(clicked()),this, SLOT(rejectExit()));
}

AddDialog::~AddDialog()
{
    delete ui;
}

void AddDialog::doneExit()
{
    if(ui->checkBox_ag->isChecked()){
        content.append("Ag ");
    }
    if(ui->checkBox_cu->isChecked()){
        content.append("Cu ");
    }
    if(ui->checkBox_cup->isChecked()){
        content.append("Cu-P ");
    }
    if(ui->checkBox_sn->isChecked()){
        content.append("Sn ");
    }
    if(ui->checkBox_in->isChecked()){
        content.append("In ");
    }
    if(ui->checkBox_sb->isChecked()){
        content.append("Sb ");
    }
    if(ui->checkBox_ni->isChecked()){
        content.append("Ni ");
    }
    if(ui->checkBox_cuzr->isChecked()){
        content.append("Cu-Zr ");
    }
    if(ui->checkBox_mn->isChecked()){
        content.append("Mn ");
    }
    if(ui->checkBox_zn->isChecked()){
        content.append("Zn ");
    }
    if(ui->checkBox_cusi->isChecked()){
        content.append("Cu-Si ");
    }
    done(0);
}

void AddDialog::rejectExit()
{
    done(-1);
}
