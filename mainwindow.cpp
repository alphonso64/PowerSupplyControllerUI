#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTextCodec>
#include <QValidator>
#include "json/json.h"
#include "actiondialog.h"
#include "util.h"
#include <QStringListModel>

#define SoftWare_Version "V1.1"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    ui->setupUi(this);
    ui->manualactionAButton->setCheckable(true);
    ui->manualactionBButton->setCheckable(true);
    ui->manualactionCButton->setCheckable(true);
    ui->manualactionDButton->setCheckable(true);
    ui->manualStartButton->setCheckable(true);
    ui->recordStartButton->setCheckable(true);

    this->setWindowFlags(Qt::CustomizeWindowHint);
	
	Util::deleteUnpluedUdiskPath();

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
    autotimer->setInterval(1000);

    ui->autoStartButton->setEnabled(false);

    uiInit();
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
    connect(recorder, SIGNAL(fileRecorded()), this, SLOT(fileRecorded()));

    connect(ui->setButton, SIGNAL(clicked()), this, SLOT(setButtonClick()));
    connect(ui->manualButton, SIGNAL(clicked()), this, SLOT(manualButtonClick()));
    connect(ui->autoButton, SIGNAL(clicked()), this, SLOT(autoButtonClick()));
    connect(ui->infoButton, SIGNAL(clicked()), this, SLOT(infoButtonClick()));
    connect(serialWorker, SIGNAL(errorDispatch(int)), this, SLOT(errorHandle(int)));
    connect(ui->softUpdateButton, SIGNAL(clicked()), this, SLOT(softUpdateButtonClick()));
    connect(ui->restartButton, SIGNAL(clicked()), this, SLOT(restartButtonClick()));
    connect(ui->firmwareUpdateButton, SIGNAL(clicked()), this, SLOT(firmwarepdateButtonClick()));

}

void MainWindow::fileRecorded()
{
    CusDialog cusDialog(File_Saved_TEXT,1);
    cusDialog.exec();
}

void MainWindow::errorHandle(int flag)
{
    if(flag == 1){
        if(autoStartFlag){
            if(auto_CusDialog!=NULL){
                auto_CusDialog->done(-1);
            }
            ui->autoStartButton->setText(Start_TEXT);
            autoStartFlag = false;
            autotimer->stop();
            autostate.cnt = 0;
            autostate.currenIndex = 0;
            ui->autoStageText->setText("");
            ui->autoStageTimeText->setText("");
            auto_index--;
            ui->autoIndexText->setText("已完成"+QString::number(auto_index)+"炉");
            QStringListModel *model =(QStringListModel *)  ui->autoListView->model();
            QModelIndex indexFromModelB = model->index(autostate.currenIndex, 0);
            ui->autoListView->setCurrentIndex(indexFromModelB);

        }
        errorPage->show();
    }else if(flag == 0){
        pcStatus.powerlevel = 0;
        ui->powerSlider->setValue(0);
        errorPage->hide();

    }
}

void MainWindow::restartButtonClick()
{
    CusDialog cusdialog(REBOOT_CHECK,0);
    if(0 == cusdialog.exec()){
        QString cmd("reboot");
        system(cmd.toStdString().c_str());
    }
}

void MainWindow::softUpdateButtonClick()
{
    QString udisk = Util::checkUDiskPath();
    if(udisk == NULL)
    {
        CusDialog cusdialog(UDISK_UNPLUGIN,1);
        cusdialog.exec();
        return;
    }
    QString path(UDISK_PATH_PREFIX + udisk);
    QString file_name = Util::checkUpdatePath(path);
    if(file_name == NULL)
    {
        CusDialog cusdialog(NO_UPDATE_FILE_DETECT,1);
        cusdialog.exec();
        return;
    }
    CusDialog cusdialog(UPDATE_PROCESSING,3);
	
    copyer->filename = QString(path+"/"+file_name);
	qDebug()<<copyer->filename;
	copyer->cusDiliag = &cusdialog;
    copyer->start();
    cusdialog.exec();
}

void MainWindow::firmwarepdateButtonClick()
{
    QString udisk = Util::checkUDiskPath();
    if(udisk == NULL)
    {
        CusDialog cusdialog(UDISK_UNPLUGIN,1);
        cusdialog.exec();
        return;
    }
    QString path(UDISK_PATH_PREFIX + udisk);
    QString file_name = Util::checkFirmWareUpdatePath(path);
    if(file_name == NULL)
    {
        CusDialog cusdialog(NO_UPDATE_FILE_DETECT,1);
        cusdialog.exec();
        return;
    }
	
    QString file_name_ = Util::checkFirmWareUpdatePath_(path);
    if(file_name_ == NULL)
    {
        CusDialog cusdialog(NO_UPDATE_FILE_DETECT,1);
        cusdialog.exec();
        return;
    }
    //CusDialog cusdialog(UPDATE_PROCESSING,3);
	CusDialog cusdialog(UPDATE_PROCESSING,3);
	serialWorker->cusdialog = &cusdialog;
    serialWorker->updateFirmWareFlag = true;
    serialWorker->path = QString(path+"/"+file_name);
	serialWorker->path_ = QString(path+"/"+file_name_);
	cusdialog.exec();
    //cusdialog.exec();
}

void MainWindow::uiInit()
{
    ui->setButton->setEnabled(false);
    ui->manualButton->setEnabled(true);
    ui->autoButton->setEnabled(true);
    ui->infoButton->setEnabled(true);
    ui->stackedWidget->setCurrentIndex(0);

    ui->powerSlider->setMinimum(0);
    ui->powerSlider->setMaximum(150);
    ui->powerSlider->setValue(0);
    ui->powerSliderLabel->setText("0/150kW");

    ui->powerSlider_2->setMinimum(0);
    ui->powerSlider_2->setMaximum(150);
    ui->powerSlider_2->setValue(0);
    ui->powerSliderLabel_2->setText("0/150kW");
    ui->powerSlider_2->setEnabled(false);
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
    ui->autoIndexText->setAlignment(Qt::AlignCenter);
    QStringListModel *model = new QStringListModel();
    ui->autoListView->setModel(model);
//    ui->autoListView->setSelectionMode(QAbstractItemView::NoSelection);

    ui->softVersionLabel->setText(SoftWare_Version);

    errorPage = new ErrorPage();
    errorPage->hide();

    recorder = new RecorderWorker();
    recorder->dpuStatus = &this->dpuStatus;
    recorder->pcStatus = &this->pcStatus;

    parser = new ParseWorker();
    copyer = new FileCopyer();

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
        auto_index--;
        ui->autoIndexText->setText("已完成"+QString::number(auto_index)+"炉");
        QStringListModel *model =(QStringListModel *)  ui->autoListView->model();
        QModelIndex indexFromModelB = model->index(autostate.currenIndex, 0);
        ui->autoListView->setCurrentIndex(indexFromModelB);

    }else{
        autostate = parser->autostate;
        if(autostate.stage.size() != 0){
            ui->autoStartButton->setText(End_TEXT);
            autoStartFlag = true;
            autostate = parser->autostate;
            autostate.cnt = 0;
            autostate.currenIndex = 0;
            auto_index++;
            ui->autoIndexText->setText("第"+QString::number(auto_index)+"炉熔炼中");
            autoProcessDisplay();
        }else{
            CusDialog cusdialog(EMPTY_FILE,0);
            cusdialog.exec();
        }
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
    auto_index = 0;
    ui->autoIndexText->setText("已完成"+QString::number(auto_index)+"炉");
    QStringListModel *model =(QStringListModel *)  ui->autoListView->model();
    model ->removeRows( 0, model->rowCount() );
    qDebug()<<"model->rowCount()"<<model->rowCount();
    model->setStringList( list);

}

void MainWindow::autoProcess()
{
    int level = autostate.root[autostate.cnt]["level"].asInt();
    pcStatus.powerlevel = level;
    ui->powerSlider->setValue(level);
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
             auto_CusDialog = &cusDialog;
             pcStatus.warningControl = true;
             if(0 == cusDialog.exec())
              {
                 auto_CusDialog = NULL;
                 pcStatus.warningControl = false;
                 qDebug()<<"done";
              }else{
                 auto_CusDialog = NULL;
                 pcStatus.warningControl = false;
                 qDebug()<<"reject";
                 return;
             }

        }else if(state.actionID  == ActionBControl){
            CusDialog cusDialog(ActionBControl_TEXT,1);
            auto_CusDialog = &cusDialog;
            pcStatus.warningControl = true;
            pcStatus.toppleControl = true;
            if(0 == cusDialog.exec())
             {
                auto_CusDialog = NULL;
                pcStatus.warningControl = false;
                pcStatus.toppleControl = false;
                qDebug()<<"done";
             }else{
                auto_CusDialog = NULL;
                pcStatus.warningControl = false;
                pcStatus.toppleControl = false;
                qDebug()<<"reject";
                return;
            }
        }else if(state.actionID  == ActionCControl){
            CusDialog cusDialog(ActionCControl_TEXT,1);
            auto_CusDialog = &cusDialog;
            pcStatus.warningControl = true;
            if(0 == cusDialog.exec())
             {
                auto_CusDialog = NULL;
                pcStatus.warningControl = false;
                qDebug()<<"done";
             }else{
                auto_CusDialog = NULL;
                pcStatus.warningControl = false;
                qDebug()<<"reject";
                return;
            }
        }else if(state.actionID  == ActionDControl){
            CusDialog cusDialog(ActionDControl_TEXT,1);
            auto_CusDialog = &cusDialog;
            pcStatus.warningControl = true;
            if(0 == cusDialog.exec())
             {
                auto_CusDialog = NULL;
                pcStatus.warningControl = false;
                qDebug()<<"done";
             }else{
                auto_CusDialog = NULL;
                pcStatus.warningControl = false;
                qDebug()<<"reject";
                return;
            }
        }
        autostate.currenIndex++;
        if(autostate.currenIndex<autostate.stage.size()){
               State state = autostate.stage.at(autostate.currenIndex);
               autostate.cnt = state.startIndex;
               autoProcessDisplay();
        }else {
            ui->autoStartButton->setText(Start_TEXT);
            autoStartFlag = false;
            autotimer->stop();
            autostate.cnt = 0;
            autostate.currenIndex = 0;
            ui->autoStageText->setText("");
            ui->autoStageTimeText->setText("");
            ui->autoIndexText->setText("已完成"+QString::number(auto_index)+"炉");
            QStringListModel *model =(QStringListModel *)  ui->autoListView->model();
            QModelIndex indexFromModelB = model->index(autostate.currenIndex, 0);
            ui->autoListView->setCurrentIndex(indexFromModelB);
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
    ui->powerSlider_2->setValue(value);
    ui->powerSliderLabel_2->setText(QString::number(value)+"/150kW");
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
    ui->displayPowerLabel->setText(QString::number(dpuStatus.power));
    ui->displayTempLabel->setText(QString::number(dpuStatus.temp_a));

    ui->displayPowerLabel_2->setText(QString::number(dpuStatus.power));
    ui->displayTempLabel_2->setText(QString::number(dpuStatus.temp_a));

    ui->displayVoltageLabel->setText(QString::number(dpuStatus.ua));
    ui->displayCurrentLabel->setText(QString::number(dpuStatus.ia));

    ui->displayVoltageLabel_2->setText(QString::number(dpuStatus.ua));
    ui->displayCurrentLabel_2->setText(QString::number(dpuStatus.ia));

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
            time.setHMS(hour,min,0);
            //time.setHMS(0,0,10);
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

//void MainWindow::groupButtonClick(int id)
//{
//    if(id == setBtnID){
//        ui->stackedWidget->setCurrentIndex(0);
//    }else if(id == manualBtnID){
//        ui->stackedWidget->setCurrentIndex(1);
//    }else if(id == autoBtnID){
//        ui->stackedWidget->setCurrentIndex(2);
//    }else if(id == infoBtnID){
//        ui->stackedWidget->setCurrentIndex(3);
//    }
//}

void MainWindow::setButtonClick()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->setButton->setEnabled(false);
    ui->manualButton->setEnabled(true);
    ui->autoButton->setEnabled(true);
    ui->infoButton->setEnabled(true);
}

void MainWindow::manualButtonClick()
{
    if(autoStartFlag){
        CusDialog cusDialog("正在自动模式下，无法切换手动模式",1);
        cusDialog.exec();
        return;
    }
    ui->stackedWidget->setCurrentIndex(1);
    ui->setButton->setEnabled(true);
    ui->manualButton->setEnabled(false);
    ui->autoButton->setEnabled(true);
    ui->infoButton->setEnabled(true);
//    qDebug()<<"valueChanged"<<pcStatus.powerlevel;
//    ui->powerSlider->setValue(pcStatus.powerlevel);
}

void MainWindow::autoButtonClick()
{
    if(recordFlag){
        CusDialog cusDialog("正在手动记录模式下，无法切换自动模式",1);
        cusDialog.exec();
        return;
    }
    ui->stackedWidget->setCurrentIndex(2);
    ui->setButton->setEnabled(true);
    ui->manualButton->setEnabled(true);
    ui->autoButton->setEnabled(false);
    ui->infoButton->setEnabled(true);
}

void MainWindow::infoButtonClick()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->setButton->setEnabled(true);
    ui->manualButton->setEnabled(true);
    ui->autoButton->setEnabled(true);
    ui->infoButton->setEnabled(false);
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
