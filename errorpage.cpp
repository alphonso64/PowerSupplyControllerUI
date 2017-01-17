#include "errorpage.h"
#include "ui_errorpage.h"

ErrorPage::ErrorPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ErrorPage)
{
    ui->setupUi(this);
    ui->label->setAlignment(Qt::AlignCenter);
}

ErrorPage::~ErrorPage()
{
    delete ui;
}

void ErrorPage::setMsg(QString msg)
{
    ui->label->setText(msg);
}
