#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTextCodec>
#include <QValidator>
#include "json/json.h"
#include "actiondialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    ui->setupUi(this);
    ui->setButton->setCheckable(true);
    ui->manualButton->setCheckable(true);
    ui->autoButton->setCheckable(true);
    ui->infoButton->setCheckable(true);
    ui->manualactionAButton->setCheckable(true);
    ui->manualactionBButton->setCheckable(true);
    ui->manualactionCButton->setCheckable(true);
    ui->manualactionDButton->setCheckable(true);
    ui->manualStartButton->setCheckable(true);
    ui->recordStartButton->setCheckable(true);

    //this->setWindowFlags(Qt::CustomizeWindowHint);

    group = new QButtonGroup(this);
    group->addButton(ui->setButton,setBtnID);
    group->addButton(ui->manualButton,manualBtnID);
    group->addButton(ui->autoButton,autoBtnID);
    group->addButton(ui->infoButton,infoBtnID);
    group->setExclusive(true);

    group_manual = new QButtonGroup(this);
    group_manual->addButton(ui->manualactionAButton,manualAID);
    group_manual->addButton(ui->manualactionBButton,manualBID);
    group_manual->addButton(ui->manualactionCButton,manualCID);
    group_manual->addButton(ui->manualactionDButton,manualDID);
    group_manual->setExclusive(false);

    QValidator* validator = new QIntValidator( 0, 600, this );
    ui->timeEdit->setValidator(validator);
    startTimerFlag = false;
    recordFlag = false;

    timer = new QTimer();
    timer->setInterval(1000);

    displaytimer = new QTimer();
    displaytimer->setInterval(300);
    displaytimer->start();

    uiInit();
    connect(group, SIGNAL(buttonClicked(int)), this, SLOT(groupButtonClick(int)));
    connect(group_manual, SIGNAL(buttonClicked(int)), this, SLOT(actionGroupButtonClick(int)));
    connect(ui->powerSlider, SIGNAL(valueChanged(int)), this, SLOT(setPowerValue(int)));
    connect(ui->manualStartButton, SIGNAL(toggled(bool)), this, SLOT(manualStartClick(bool)));
    connect(ui->recordStartButton, SIGNAL(toggled(bool)), this, SLOT(recordStartClick(bool)));
    connect(timer, SIGNAL(timeout()), this, SLOT(timerOut()));
    connect(displaytimer, SIGNAL(timeout()), this, SLOT(display()));

}

void MainWindow::uiInit()
{
    ui->setButton->setChecked(true);
    ui->stackedWidget->setCurrentIndex(0);

    ui->powerSlider->setMinimum(0);
    ui->powerSlider->setMaximum(150);
    ui->powerSlider->setValue(0);
    ui->powerSliderLabel->setText("0/150kW");
    ui->manualStartButton->setChecked(false);

    ui->displayTempLabel->setText("");
    ui->displayControlLabel->setText("");
    ui->displayPowerLabel->setText("");
    ui->displayWarningLabel->setText("");


}

void MainWindow::setPowerValue(int value)
{
    ui->powerSliderLabel->setText(QString::number(value)+"/150kW");
}

void MainWindow::timerOut()
{
    time = time.addSecs(-1);
    ui->manualtimelabel->setText(time.toString("hh:mm:ss"));
    if(time.hour() == 0 && time.minute() == 0 && time.second() == 0){
        ui->manualtimelabel->setText("");
        startTimerFlag = false;
        ui->manualStartButton->setText("开始");
        timer->stop();
        pcStatus.warningControl = true;
        CusDialog cusdialog("计时器报警!",1);
        cusdialog.exec();
        pcStatus.warningControl = false;
    }

}

void MainWindow::display()
{
    dpuStatus.power++;
    ui->displayPowerLabel->setText(QString::number(dpuStatus.power));
    ui->displayTempLabel->setText(QString::number(dpuStatus.temp_a));
    if(pcStatus.toppleControl){
       ui->displayControlLabel->setText("未锁定") ;
    }else{
       ui->displayControlLabel->setText("锁定") ;
    }

    if(pcStatus.warningControl){
       ui->displayWarningLabel->setText("报警") ;
    }else{
       ui->displayWarningLabel->setText("未报警") ;
    }
}

void MainWindow::recordStartClick(bool flag)
{
    if(recordFlag){
        recordFlag = false;
        ui->recordStartButton->setText("开始记录");
    }else{
        recordFlag = true;
        ui->recordStartButton->setText("停止记录");
    }
}

void MainWindow::manualStartClick(bool flag)
{
    if(!startTimerFlag){
        int value = ui->timeEdit->text().toInt();
        if(value>0){
            startTimerFlag = true;
            ui->manualStartButton->setText("停止");
            int hour = value/60;
            int min = value%60;
            //time.setHMS(hour,min,0);
            time.setHMS(0,0,10);
            ui->manualtimelabel->setText(time.toString("hh:mm:ss"));
            timer->start();
        }else{
            CusDialog cusdialog("请先输入定时时间!",1);
            qDebug()<<cusdialog.exec();
        }
    }else{
        startTimerFlag = false;
        ui->manualStartButton->setText("开始");
        timer->stop();
    }
}

void MainWindow::groupButtonClick(int id)
{
    if(id == setBtnID){
        ui->stackedWidget->setCurrentIndex(0);
    }else if(id == manualBtnID){
        ui->stackedWidget->setCurrentIndex(1);
    }else if(id == autoBtnID){
        ui->stackedWidget->setCurrentIndex(2);
    }else if(id == infoBtnID){
        ui->stackedWidget->setCurrentIndex(3);
    }
}

void MainWindow::actionGroupButtonClick(int id)
{
    if(timer->isActive()){
        ui->manualtimelabel->setText("");
        startTimerFlag = false;
        ui->manualStartButton->setText("开始");
        timer->stop();
    }

    if(id == manualAID){
        CusDialog cusdialog("操作:加料",0);
        cusdialog.exec();
    }else if(id == manualBID){
        pcStatus.toppleControl = true;
        CusDialog cusdialog("操作:倒包",0);
        cusdialog.exec();
        pcStatus.toppleControl = false;
    }else if(id == manualCID){
        CusDialog cusdialog("操作:捞渣",0);
        cusdialog.exec();
    }else if(id == manualDID){
        CusDialog cusdialog("操作:搅拌",0);
        cusdialog.exec();
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}
