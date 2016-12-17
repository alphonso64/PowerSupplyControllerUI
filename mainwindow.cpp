#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTextCodec>
#include <QValidator>
#include "json/json.h"
#include "actiondialog.h"
#include "util.h"
#include <QStringListModel>

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
    autoStartFlag = false;

    timer = new QTimer();
    timer->setInterval(1000);

    displaytimer = new QTimer();
    displaytimer->setInterval(300);
    displaytimer->start();

    autotimer = new QTimer();
    autotimer->setInterval(50);

    ui->autoStartButton->setEnabled(false);

    uiInit();
    connect(group, SIGNAL(buttonClicked(int)), this, SLOT(groupButtonClick(int)));
    connect(group_manual, SIGNAL(buttonClicked(int)), this, SLOT(actionGroupButtonClick(int)));
    connect(ui->powerSlider, SIGNAL(valueChanged(int)), this, SLOT(setPowerValue(int)));
    connect(ui->manualStartButton, SIGNAL(toggled(bool)), this, SLOT(manualStartClick(bool)));
    connect(ui->recordStartButton, SIGNAL(toggled(bool)), this, SLOT(recordStartClick(bool)));
    connect(timer, SIGNAL(timeout()), this, SLOT(timerOut()));
    connect(displaytimer, SIGNAL(timeout()), this, SLOT(display()));
    connect(this, SIGNAL(recordStatus()), recorder, SLOT(actionRecord()));
    connect(ui->openFileButton, SIGNAL(clicked()), this, SLOT(fileOpen()));
    connect(parser, SIGNAL(parsed()), this, SLOT(fileParsed()));
    connect(autotimer, SIGNAL(timeout()), this, SLOT(autoProcess()));
    connect(ui->autoStartButton, SIGNAL(clicked()), this, SLOT(autoStartClick()));
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

    ui->displayTempLabel_2->setText("");
    ui->displayControlLabel_2->setText("");
    ui->displayPowerLabel_2->setText("");
    ui->displayWarningLabel_2->setText("");

    ui->autoStageText->setAlignment(Qt::AlignCenter);
    ui->autoStageTimeText->setAlignment(Qt::AlignCenter);

    QStringListModel *model = new QStringListModel();
    ui->autoListView->setModel(model);
//    ui->autoListView->setSelectionMode(QAbstractItemView::NoSelection);

    recorder = new RecorderWorker();
    recorder->dpuStatus = &this->dpuStatus;
    recorder->pcStatus = &this->pcStatus;

    parser = new ParseWorker();

    serialWorker = new SerialWorker();
	serialWorker->dpuStatus = &this->dpuStatus;
	serialWorker->pcStatus = &this->pcStatus;
    serialWorker->start();
}

void MainWindow::autoStartClick()
{
    if(autoStartFlag){
        ui->autoStartButton->setText(Start_TEXT);
        autoStartFlag = false;
        autotimer->stop();
        autostate.cnt = 0;
        autostate.currenIndex = 0;
        ui->autoStageText->setText("");
        ui->autoStageTimeText->setText("");
        QStringListModel *model =(QStringListModel *)  ui->autoListView->model();
        QModelIndex indexFromModelB = model->index(autostate.currenIndex, 0);
        ui->autoListView->setCurrentIndex(indexFromModelB);

    }else{
        ui->autoStartButton->setText(End_TEXT);
        autoStartFlag = true;
        autostate = parser->autostate;
        autostate.cnt = 0;
        autostate.currenIndex = 0;
        autoProcessDisplay();

    }
}

void MainWindow::autoProcessDisplay()
{
    QStringListModel *model =(QStringListModel *)  ui->autoListView->model();
    QModelIndex indexFromModelB = model->index(autostate.currenIndex, 0);
    ui->autoListView->setCurrentIndex(indexFromModelB);

    QString val(Step_TEXT+QString::number(autostate.currenIndex+1));
    ui->autoStageText->setText(val);
    State state = autostate.stage.at(autostate.currenIndex);
    int value = state.actionStartIndex-state.startIndex;

    int min = value/60;
    int hour;
    if(min>59){
        hour = min/60;
        min = min%60;
    }else{
        hour = 0;
    }
    int secend = value%60;
    autotime.setHMS(hour,min,secend);
    ui->autoStageTimeText->setText(autotime.toString("hh:mm:ss"));
    autotimer->start();
}

void MainWindow::fileParsed()
{
    ui->autoStartButton->setEnabled(true);
    AutoState autostate = parser->autostate;
    QStringList list;
    for(int i=0;i<autostate.stage.size();i++){
        State state = autostate.stage.at(i);
        QString val(Step_TEXT+QString::number(i+1)+": ");

        int second = state.actionStartIndex - state.startIndex;

        QString temp;
        temp.sprintf("%3d分%2d秒  后 ",second/60,second%60);

        int acion = state.actionID;
        if(acion == ActionAControl){
            temp.append(ActionAControl_TEXT);
        }else if(acion == ActionBControl){
            temp.append(ActionBControl_TEXT);
        }else if(acion == ActionCControl){
            temp.append(ActionCControl_TEXT);
        }else if(acion == ActionDControl){
            temp.append(ActionDControl_TEXT);
        }
        list.append(val+temp);
    }
    QStringListModel *model =(QStringListModel *)  ui->autoListView->model();
    model ->removeRows( 0, model->rowCount() );
    qDebug()<<"model->rowCount()"<<model->rowCount();
    model->setStringList( list);

}

void MainWindow::autoProcess()
{
    int level = autostate.root[autostate.cnt]["level"].asInt();
    pcStatus.powerlevel = level;
    qDebug()<<"level"<<level;

    autostate.cnt++;
//    qDebug()<<autostate.root[autostate.cnt]["index"].asInt()<<" "<<autostate.root[autostate.cnt]["action"].asInt();
    autotime = autotime.addSecs(-1);
    ui->autoStageTimeText->setText(autotime.toString("hh:mm:ss"));

    if(autotime.hour() == 0 && autotime.minute() == 0 && autotime.second() == 0){
        autotimer->stop();
        State state = autostate.stage.at(autostate.currenIndex);
        if(state.actionID == ActionAControl){
             CusDialog cusDialog(ActionAControl_TEXT,1);
             cusDialog.exec();
        }else if(state.actionID  == ActionBControl){
            CusDialog cusDialog(ActionBControl_TEXT,1);
            cusDialog.exec();
        }else if(state.actionID  == ActionCControl){
            CusDialog cusDialog(ActionCControl_TEXT,1);
            cusDialog.exec();
        }else if(state.actionID  == ActionDControl){
            CusDialog cusDialog(ActionDControl_TEXT,1);
            cusDialog.exec();
        }
        autostate.currenIndex++;
        if(autostate.currenIndex<autostate.stage.size()){
               State state = autostate.stage.at(autostate.currenIndex);
               autostate.cnt = state.startIndex;
               autoProcessDisplay();
        }
    }
}

void MainWindow::fileOpen()
{
    ActionDialog actionDialog;
    if(0 == actionDialog.exec())
    {
        ui->fileNameText->setText(actionDialog.fileName);
        if(actionDialog.fileName.length()>0){
//            ui->autoStartButton->setEnabled(true);
            parser->fileName = actionDialog.fileName;
            parser->start();
        }
    }
}

void MainWindow::setPowerValue(int value)
{
    ui->powerSliderLabel->setText(QString::number(value)+"/150kW");
    pcStatus.powerlevel = value;
}

void MainWindow::timerOut()
{
    time = time.addSecs(-1);
    ui->manualtimelabel->setText(time.toString("hh:mm:ss"));
    if(time.hour() == 0 && time.minute() == 0 && time.second() == 0){
        ui->manualtimelabel->setText("");
        startTimerFlag = false;
        ui->manualStartButton->setText(Start_TEXT);
        timer->stop();
        pcStatus.warningControl = true;
        CusDialog cusdialog(Warning_Timer_TEXT,1);
        cusdialog.exec();
        pcStatus.warningControl = false;
    }

}

void MainWindow::display()
{
    dpuStatus.power++;
    ui->displayPowerLabel->setText(QString::number(dpuStatus.power));
    ui->displayTempLabel->setText(QString::number(dpuStatus.temp_a));

    ui->displayPowerLabel_2->setText(QString::number(dpuStatus.power));
    ui->displayTempLabel_2->setText(QString::number(dpuStatus.temp_a));
    if(pcStatus.toppleControl){
       ui->displayControlLabel->setText(State_UNLOCK_TEXT) ;
       ui->displayControlLabel_2->setText(State_UNLOCK_TEXT) ;
    }else{
       ui->displayControlLabel->setText(State_LOCK_TEXT) ;
       ui->displayControlLabel_2->setText(State_LOCK_TEXT) ;
    }

    if(pcStatus.warningControl){
       ui->displayWarningLabel->setText(State_Warning_TEXT) ;
       ui->displayWarningLabel_2->setText(State_Warning_TEXT) ;
    }else{
       ui->displayWarningLabel->setText(State_NO_Warning_TEXT) ;
       ui->displayWarningLabel_2->setText(State_NO_Warning_TEXT) ;
    }
}

void MainWindow::recordStartClick(bool flag)
{    
    if(recordFlag){
        recordFlag = false;
        ui->recordStartButton->setText(Start_Record_TEXT);
        recorder->exit();
        ui->fileNameEdit->setEnabled(true);
    }else{
        QString fileName = ui->fileNameEdit->text();
        if(fileName.length() == 0){
            CusDialog cusdialog(Warning_NO_FILENAME_TEXT,1);
            cusdialog.exec();
            return;
        }
        ui->fileNameEdit->setEnabled(false);
        recordFlag = true;
        ui->recordStartButton->setText(End_Record__TEXT);
        recorder->fileName = fileName;
        recorder->start();
    }
}


void MainWindow::manualStartClick(bool flag)
{
    if(!startTimerFlag){
        int value = ui->timeEdit->text().toInt();
        if(value>0){
            startTimerFlag = true;
            ui->manualStartButton->setText(End_TEXT);
            int hour = value/60;
            int min = value%60;
            //time.setHMS(hour,min,0);
            time.setHMS(0,0,10);
            ui->manualtimelabel->setText(time.toString("hh:mm:ss"));
            timer->start();
        }else{
            CusDialog cusdialog(Warning_NO_TIME_TEXT,1);
            qDebug()<<cusdialog.exec();
        }
    }else{
        startTimerFlag = false;
        ui->manualStartButton->setText(Start_TEXT);
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
        ui->manualStartButton->setText(Start_TEXT);
        timer->stop();
    }
    if(recordFlag){
       emit(recordStatus());
    }
    if(id == manualAID){
        CusDialog cusdialog(ActionAControl_TEXT,0);
        pcStatus.action = ActionAControl;
        pcStatus.actionState = ActionState_UNDO;
        int val = cusdialog.exec();
        if(val == 0){
            pcStatus.action = NOAction;
            pcStatus.actionState = ActionState_DONE;
        }else if(val == -1){
            pcStatus.action = NOAction;
            pcStatus.actionState = ActionState_UNDO;
        }
    }else if(id == manualBID){
        pcStatus.toppleControl = true;
        CusDialog cusdialog(ActionBControl_TEXT,0);
        pcStatus.action = ActionBControl;
        pcStatus.actionState = ActionState_UNDO;
        int val = cusdialog.exec();
        pcStatus.toppleControl = false;
        if(val == 0){
            pcStatus.action = NOAction;
            pcStatus.actionState = ActionState_DONE;
        }else if(val == -1){
            pcStatus.action = NOAction;
            pcStatus.actionState = ActionState_UNDO;
        }
    }else if(id == manualCID){
        CusDialog cusdialog(ActionCControl_TEXT,0);
        pcStatus.action = ActionCControl;
        pcStatus.actionState = ActionState_UNDO;
        int val = cusdialog.exec();
        if(val == 0){
            pcStatus.action = NOAction;
            pcStatus.actionState = ActionState_DONE;
        }else if(val == -1){
            pcStatus.action = NOAction;
            pcStatus.actionState = ActionState_UNDO;
        }
    }else if(id == manualDID){
        CusDialog cusdialog(ActionDControl_TEXT,0);
        pcStatus.action = ActionDControl;
        pcStatus.actionState = ActionState_UNDO;
        int val = cusdialog.exec();
        if(val == 0){
            pcStatus.action = NOAction;
            pcStatus.actionState = ActionState_DONE;
        }else if(val == -1){
            pcStatus.action = NOAction;
            pcStatus.actionState = ActionState_UNDO;
        }
    }
    if(recordFlag){
       emit(recordStatus());
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}
