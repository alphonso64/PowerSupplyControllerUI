#include "actiondialog.h"
#include "ui_actiondialog.h"

ActionDialog::ActionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ActionDialog)
{
    ui->setupUi(this);
}

ActionDialog::ActionDialog(QString msg,int ID,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ActionDialog)
{
    ui->setupUi(this);
    ui->label->setText(msg);
    ui->label->setAlignment(Qt::AlignCenter);
    flagID = ID;
    connect(ui->doneButton, SIGNAL(clicked()),this, SLOT(exit()));
    connect(ui->rejectButton, SIGNAL(clicked()),this, SLOT(exit()));
}

void ActionDialog::rejectExit()
{
    done(-1);
}

void ActionDialog::doneExit()
{
    done(0);
}

ActionDialog::~ActionDialog()
{
    delete ui;
}
