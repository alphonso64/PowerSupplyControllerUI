﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTextCodec>
#include <QValidator>
#include "json/json.h"
#include "actiondialog.h"
#include "util.h"
#include <QStringListModel>

#define SoftWare_Version "V1.4"

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

    nettimer =  new QTimer();
    nettimer->setInterval(10000);
    nettimer->start();

    acctimer = new QTimer();
    acctimer->setInterval(1000);

   // ui->fileUploadButton->setVisible(false);
    ui->autoStartButton->setEnabled(false);

    nam = new QNetworkAccessManager(this);

    netStartFlag = false;
    netStateFlag = false;

    ui->netLabel->setPixmap(QPixmap(NETOFF_PIC_PATH));
    ui->netLabel_2->setPixmap(QPixmap(NETOFF_PIC_PATH));

    uiInit();
    connect(group_manual, SIGNAL(buttonClicked(int)), this, SLOT(actionGroupButtonClick(int)));
    connect(ui->powerSlider, SIGNAL(valueChanged(int)), this, SLOT(setPowerValue(int)));
    connect(ui->manualStartButton, SIGNAL(toggled(bool)), this, SLOT(manualStartClick(bool)));
    connect(ui->recordStartButton, SIGNAL(toggled(bool)), this, SLOT(recordStartClick(bool)));
    connect(timer, SIGNAL(timeout()), this, SLOT(timerOut()));
    connect(nettimer, SIGNAL(timeout()), this, SLOT(stateUpload()));
    connect(acctimer, SIGNAL(timeout()), this, SLOT(acctimerOut()));
    connect(displaytimer, SIGNAL(timeout()), this, SLOT(display()));
    connect(this, SIGNAL(recordStatus()), recorder, SLOT(actionRecord()));
    connect(this, SIGNAL(recordStatus(QString)), recorder, SLOT(actionRecord(QString)));
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
    connect(serialWorker, SIGNAL(errorDismiss(int)), this, SLOT(errorDismissHandle(int)));
    connect(ui->softUpdateButton, SIGNAL(clicked()), this, SLOT(softUpdateButtonClick()));
    connect(ui->restartButton, SIGNAL(clicked()), this, SLOT(restartButtonClick()));
    connect(ui->fileUploadButton, SIGNAL(clicked()), this, SLOT(fileUpload()));
    connect(ui->fileDownloadButton, SIGNAL(clicked()), this, SLOT(fileDownload()));
    connect(ui->firmwareUpdateButton, SIGNAL(clicked()), this, SLOT(firmwarepdateButtonClick()));
    connect(ui->manualAddButton, SIGNAL(clicked()), this, SLOT(manualAdd()));
    connect(ui->manualMinusButton, SIGNAL(clicked()), this, SLOT(manualMinus()));

    //qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
}

void MainWindow::manualAdd()
{
    int value = ui->powerSlider->value();
    if(value<MAX_POWER_VALUE)
    {
        value++;
    }
    ui->powerSlider->setValue(value);
    setPowerValue(value);
}

void MainWindow::manualMinus()
{
    int value = ui->powerSlider->value();
    if(value>MIN_POWER_VALUE)
    {
        value--;
    }
    ui->powerSlider->setValue(value);
    setPowerValue(value);
}

void MainWindow::acctimerOut()
{
    acctime = acctime.addSecs(1);
    ui->acctimelabel->setText(acctime.toString("hh:mm:ss"));
}

void MainWindow::fileUploadfinished()
{
    if (file_reply->error() == QNetworkReply::NoError)
    {
        qDebug()<<"upload done";
        fileupload_CusDialog->changeStyle(UPLOAD_FILE_STATE_SUCCESS,1);
    }
    else
    {
        qDebug()<<"upload err";
        fileupload_CusDialog->changeStyle(UPLOAD_FILE_STATE_FAIL,1);
    }
    file_reply->deleteLater();
}

void MainWindow::fileUpload()
{
    ActionDialog actionDialog;
    actionDialog.setStyle(0);
    if(0 == actionDialog.exec())
    {
        QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
        QHttpPart imagePart;
        imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\""+ actionDialog.fileName +"\""));/* version.tkt is the name on my Disk of the file that I want to upload */

        QHttpPart textPart;
        textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"filepath\""));
        textPart.setBody("toto");/* toto is the name I give to my file in the server */

        QFile *file = new QFile(PrePath+actionDialog.fileName);
        file->open(QIODevice::ReadOnly);
        imagePart.setBodyDevice(file);
        file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart

        multiPart->append(textPart);
        multiPart->append(imagePart);

        QUrl url("http://192.168.3.21:8089/PowerMonitor/rest/api/uploadFile");
        QNetworkRequest request(url);
        mutex.lock();
        file_reply = nam->post(request, multiPart);
        mutex.unlock();
        multiPart->setParent(file_reply); // delete the multiPart with the reply
        connect(file_reply, SIGNAL(finished()), this, SLOT(fileUploadfinished()));
        fileupload_CusDialog = new CusDialog(UPLOAD_FILE_STATE_PROCESSING,3);
        fileupload_CusDialog->exec();
        delete fileupload_CusDialog;
        fileupload_CusDialog = NULL;
    }
}

void MainWindow::fileDownload()
{
    QUrl url("http://192.168.3.21:8089/PowerMonitor/rest/api/getFileList");
    QNetworkRequest request(url);
    mutex.lock();
    file_reply = nam->post(request,QByteArray(0));
    mutex.unlock();
    connect(file_reply, SIGNAL(finished()), this, SLOT(fileListDownloadinished()));
    fileupload_CusDialog = new CusDialog(DOWN_FILE_LIST_PROCESSING,3);
    fileupload_CusDialog->exec();
}

void MainWindow::fileListDownloadinished()
{
    if (file_reply->error() == QNetworkReply::NoError)
    {
        fileupload_CusDialog->done(1);
        QByteArray res = file_reply->readAll();
        QMap<QString,QString> fileList = Util::parseFileList(res);
        ActionDialog dialog;
        dialog.list = fileList;
        dialog.setStyle(1);
        if(0 == dialog.exec())
        {
            qDebug()<<fileList[dialog.fileName];
            QString url_pre("http://192.168.3.21:8089/PowerMonitor/rest/api/reqFile?path=");
            url_pre.append(fileList[dialog.fileName]);
            downFileName = dialog.fileName;
            QUrl url(url_pre);
            QNetworkRequest request(url);
            mutex.lock();
            file_down_reply = nam->get(request);
            mutex.unlock();
            connect(file_down_reply, SIGNAL(finished()), this, SLOT(fileDownloadinished()));
            fileupload_CusDialog = new CusDialog(UPLOAD_FILE_PROCESSING,3);
            fileupload_CusDialog->exec();

        }
    }
    else
    {
        fileupload_CusDialog->changeStyle(DOWN_FILE_LIST_FAIL,1);
    }
    file_reply->deleteLater();
}

void MainWindow::fileDownloadinished()
{
    if (file_down_reply->error() == QNetworkReply::NoError)
    {
        QFile data(PrePath+downFileName);
        if (data.open(QFile::WriteOnly | QIODevice::Truncate)) {
            QTextStream out(&data);
            out << file_down_reply->readAll();
        }
        fileupload_CusDialog->changeStyle(DOWN_FILE_STATE_SUCCESS,1);
    }
    else
    {
        fileupload_CusDialog->changeStyle(DOWN_FILE_STATE_FAIL,1);
    }
    file_down_reply->deleteLater();
}



void MainWindow::netfinished()
{
    if (state_reply->error() == QNetworkReply::NoError)
    {
        if(!netStateFlag){
            ui->netLabel->setPixmap(QPixmap(NET_PIC_PATH));
            ui->netLabel_2->setPixmap(QPixmap(NET_PIC_PATH));
        }
        netStateFlag = true;
        qDebug()<<"handle ok here";
    }
    else
    {
        if(netStateFlag){
            ui->netLabel->setPixmap(QPixmap(NETOFF_PIC_PATH));
            ui->netLabel_2->setPixmap(QPixmap(NETOFF_PIC_PATH));
        }
        netStateFlag = false;
        qDebug()<<"handle errors here";
    }
    state_reply->deleteLater();
    netStartFlag = false;
}

void MainWindow::stateUpload()
{
    if(!netStartFlag){
        netStartFlag = true;
        qDebug()<<"stateUpload";
        Json::FastWriter writer;
        Json::Value status;
        status["temp_a"] = QString::number(dpuStatus.temp_a).toStdString();
        status["temp_b"] = QString::number(dpuStatus.temp_b).toStdString();
        status["ua"] = QString::number(dpuStatus.ua).toStdString();
        status["ia"] = QString::number(dpuStatus.ia).toStdString();
        status["power"] = QString::number(dpuStatus.power).toStdString();
        status["errorcode"] = QString::number(dpuStatus.errorcode).toStdString();
        status["powerlevel"] = QString::number(pcStatus.powerlevel).toStdString();
        std::string json_file = writer.write(status);

        QUrl url("http://10.18.1.24:8080/PowerMonitor/rest/api/uploadStatus");
        QByteArray array(json_file.c_str());
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader,QVariant("application/json"));
        mutex.lock();
        state_reply = nam->post(request,array);
        mutex.unlock();
        connect(state_reply, SIGNAL(finished()), this, SLOT(netfinished()));
    }
}

void MainWindow::fileRecorded()
{
    CusDialog cusDialog(File_Saved_TEXT,1);
    cusDialog.exec();
}

void MainWindow::errorHandle(int code)
{
    if(code & 0x01 == 1){
        pcStatus.state = false;
        ui->openFileButton->setEnabled(true);
        pcStatus.powerlevel = 0;
        ui->powerSlider->setValue(0);
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
            auto_index = 0 ;
            ui->autoIndexText->setText("");
            QStringListModel *model =(QStringListModel *)  ui->autoListView->model();
            model ->removeRows( 0, model->rowCount() );
            ui->autoStartButton->setEnabled(false);
            ui->fileNameText->setText("");
        }
        qDebug()<<"recordFlag"<<recordFlag<<" startTimerFlag"<<startTimerFlag;
        if(recordFlag){
            recordFlag = false;
            ui->recordStartButton->setText(Start_Record_TEXT);
            recorder->exit(-1);
            ui->fileNameEdit->setEnabled(true);

            if(startTimerFlag){
                startTimerFlag = false;
                ui->manualStartButton->setText(TIME_START_TEXT);
                ui->manualtimelabel->setText("");
                ui->timeEdit->setText("");
                timer->stop();

            }
            ui->acctimelabel->setText("");
            acctimer->stop();
            ui->manualStartButton->setEnabled(false);
        }
        errorPage->setMsg(EMERGENCY_STOP);
        errorPage->show();
    }
    if( (code>>1) & 0x01 == 1){
        pcStatus.state = false;
        ui->openFileButton->setEnabled(true);
        pcStatus.powerlevel = 0;
        ui->powerSlider->setValue(0);
        if(recordFlag){
            recordFlag = false;
            ui->recordStartButton->setText(Start_Record_TEXT);
            recorder->exit(-1);
            ui->fileNameEdit->setEnabled(true);
            ui->fileNameText->setText("");

            if(startTimerFlag){
                startTimerFlag = false;
                ui->manualStartButton->setText(TIME_START_TEXT);
                ui->manualtimelabel->setText("");
                ui->timeEdit->setText("");
                timer->stop();
            }
            ui->acctimelabel->setText("");
            acctimer->stop();
            ui->manualStartButton->setEnabled(false);
        }
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
            auto_index = 0 ;
            ui->autoIndexText->setText("");
            QStringListModel *model =(QStringListModel *)  ui->autoListView->model();
            model ->removeRows( 0, model->rowCount() );
            ui->autoStartButton->setEnabled(false);
            ui->fileNameText->setText("");

        }
        errorPage->setMsg(STATE_STANDBY);
        errorPage->show();
    }
    if(dpuStatus.errorcode &0x11 == 0x11){
        errorPage->setMsg(EMERGENCY_STOP);
        errorPage->show();
    }
    if( (code>>2) & 0x01 == 1){
        if(autoStartFlag){
            if(auto_CusDialog!=NULL){
                auto_CusDialog->done(-1);
            }
            ui->autoStartButton->setText(Start_TEXT);
            autoStartFlag = false;
            pcStatus.state = false;
            ui->openFileButton->setEnabled(true);
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
        ui->stateLabel->setVisible(false);
        ui->stateLabel_2->setVisible(false);
        ui->stateErrLabel->setVisible(true);
        ui->stateErrLabel_2->setVisible(true);
        ui->stateErrLabel->setText(STATE_FAULT);
        ui->stateErrLabel_2->setText(STATE_FAULT);
    }
    if( (code>>3) & 0x01 == 1){
        ui->stateLabel->setVisible(false);
        ui->stateLabel_2->setVisible(true);
        ui->stateErrLabel->setVisible(true);
        ui->stateErrLabel_2->setVisible(true);
        ui->stateErrLabel->setText(STATE_LOW_EFFICIENCY);
        ui->stateErrLabel_2->setText(STATE_LOW_EFFICIENCY);
    }
}

void MainWindow::errorDismissHandle(int code)
{
    if(dpuStatus.errorcode & 0x01 ==1 ){
        errorPage->setMsg(EMERGENCY_STOP);
    }else if ((dpuStatus.errorcode >>1 )& 0x01 ==1){
        errorPage->setMsg(STATE_STANDBY);
    }else{
        errorPage->hide();
    }
    if( (code>>2) & 0x01 == 1){
        ui->stateLabel->setVisible(true);
        ui->stateLabel_2->setVisible(true);
        ui->stateErrLabel->setVisible(false);
        ui->stateErrLabel_2->setVisible(false);
    }
    if( (code>>3) & 0x01 == 1){
        ui->stateLabel->setVisible(true);
        ui->stateLabel_2->setVisible(true);
        ui->stateErrLabel->setVisible(false);
        ui->stateErrLabel_2->setVisible(false);
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

	CusDialog cusdialog(UPDATE_PROCESSING,3);
	serialWorker->cusdialog = &cusdialog;
    serialWorker->updateFirmWareFlag = true;
    serialWorker->path = QString(path+"/"+file_name);
	serialWorker->path_ = QString(path+"/"+file_name_);
    cusdialog.exec();
}

void MainWindow::uiInit()
{
    ui->setButton->setEnabled(false);
    ui->manualButton->setEnabled(true);
    ui->autoButton->setEnabled(true);
    ui->infoButton->setEnabled(true);
    ui->stackedWidget->setCurrentIndex(0);

    ui->powerSlider->setMinimum(MIN_POWER_VALUE);
    ui->powerSlider->setMaximum(MAX_POWER_VALUE);
    ui->powerSlider->setValue(0);
    ui->powerSliderLabel->setText("0/100%");

    ui->powerSlider_2->setMinimum(MIN_POWER_VALUE);
    ui->powerSlider_2->setMaximum(MAX_POWER_VALUE);
    ui->powerSlider_2->setValue(0);
    ui->powerSliderLabel_2->setText("0/100%");
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

    ui->stateErrLabel->setVisible(false);
    ui->stateErrLabel_2->setVisible(false);

    warn_CusDialog = NULL;
    auto_CusDialog = NULL;

    ui->manualStartButton->setEnabled(false);

    ui->autoStageText->setAlignment(Qt::AlignCenter);
    ui->autoStageTimeText->setAlignment(Qt::AlignCenter);
    ui->autoIndexText->setAlignment(Qt::AlignCenter);
    QStringListModel *model = new QStringListModel();
    ui->autoListView->setModel(model);
    ui->autoListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    ui->autoListView->setSelectionMode(QAbstractItemView::NoSelection);

    ui->softVersionLabel->setText(SoftWare_Version);

    errorPage = new ErrorPage();
    errorPage->hide();

    recorder = new RecorderWorker();
    recorder->dpuStatus = &this->dpuStatus;
    recorder->pcStatus = &this->pcStatus;

    parser = new ParseWorker();
    copyer = new FileCopyer();

    rfreader = new RFReader();
    rfreader->start();

    serialWorker = new SerialWorker();
	serialWorker->dpuStatus = &this->dpuStatus;
	serialWorker->pcStatus = &this->pcStatus;
    serialWorker->start();
}

void MainWindow::autoStartClick()
{
    if(autoStartFlag){
        pcStatus.state =  false;
        ui->openFileButton->setEnabled(true);
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
        if((dpuStatus.errorcode>>2) & 0x01 == 1){
            CusDialog cusdialog(MSG_AUTO_STATE_FAULT,1);
            cusdialog.exec();
            return;
        }
        if((dpuStatus.errorcode>>3) & 0x01 == 1){
            CusDialog cusdialog(MSG_AUTO_STATE_LOW_EFFICIENCY,1);
            cusdialog.exec();
            return;
        }
        autostate = parser->autostate;
        if(autostate.stage.size() != 0){
            pcStatus.state = true;
            ui->openFileButton->setEnabled(false);
            ui->autoStartButton->setText(End_TEXT);
            autoStartFlag = true;
            autostate = parser->autostate;
            autostate.cnt = 0;
            autostate.currenIndex = 0;
            auto_index++;
            ui->autoIndexText->setText("第"+QString::number(auto_index)+"炉熔炼中");
            autoProcessDisplay();
        }else{
            CusDialog cusdialog(EMPTY_FILE,1);
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
            temp.append(" ");
            temp.append(state.content);
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
        if(warn_CusDialog != NULL){
            warn_CusDialog->reject();
        }
        if(state.actionID == ActionAControl){
             QString val = ActionAControl_TEXT;
             val.append("\n");
             val.append(state.content);
             auto_CusDialog = new CusDialog(val,1);
             pcStatus.warningControl = true;
             if(0 == auto_CusDialog->exec())
              {
                 delete auto_CusDialog;
                 auto_CusDialog = NULL;
                 pcStatus.warningControl = false;
                 qDebug()<<"done";
              }else{
                 delete auto_CusDialog;
                 auto_CusDialog = NULL;
                 pcStatus.warningControl = false;
                 qDebug()<<"reject";
                 return;
             }

        }else if(state.actionID  == ActionBControl){
            auto_CusDialog = new CusDialog(ActionBControl_TEXT,1);
            pcStatus.warningControl = true;
            pcStatus.toppleControl = true;
            if(0 == auto_CusDialog->exec())
             {
                delete auto_CusDialog;
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
            auto_CusDialog = new CusDialog(ActionCControl_TEXT,1);
            pcStatus.warningControl = true;
            if(0 == auto_CusDialog->exec())
             {
                delete auto_CusDialog;
                auto_CusDialog = NULL;
                pcStatus.warningControl = false;
                qDebug()<<"done";
             }else{
                delete auto_CusDialog;
                auto_CusDialog = NULL;
                pcStatus.warningControl = false;
                qDebug()<<"reject";
                return;
            }
        }else if(state.actionID  == ActionDControl){
            auto_CusDialog = new CusDialog(ActionDControl_TEXT,1);
            pcStatus.warningControl = true;
            if(0 == auto_CusDialog->exec())
             {
                delete auto_CusDialog;
                auto_CusDialog = NULL;
                pcStatus.warningControl = false;
                qDebug()<<"done";
             }else{
                delete auto_CusDialog;
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
            pcStatus.state = false;
            ui->openFileButton->setEnabled(true);
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
    actionDialog.setStyle(0);
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
    ui->powerSliderLabel->setText(QString::number(value)+"/100%");
    ui->powerSlider_2->setValue(value);
    ui->powerSliderLabel_2->setText(QString::number(value)+"/100%");
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
//    dpuStatus.temp_a = qrand()%1400;
//    dpuStatus.ua = qrand()%500;
//    dpuStatus.ia = qrand()%300;
//    dpuStatus.power = qrand()%500;

    ui->displayPowerLabel->setText(QString::number(dpuStatus.power));
    ui->displayTempLabel->setText(QString::number(dpuStatus.temp_a));

    ui->displayPowerLabel_2->setText(QString::number(dpuStatus.power));
    ui->displayTempLabel_2->setText(QString::number(dpuStatus.temp_a));

    ui->displayVoltageLabel->setText(QString::number(dpuStatus.ua));
    ui->displayCurrentLabel->setText(QString::number(dpuStatus.ia));

    ui->displayVoltageLabel_2->setText(QString::number(dpuStatus.ua));
    ui->displayCurrentLabel_2->setText(QString::number(dpuStatus.ia));

    if(!pcStatus.state){
        ui->displayControlLabel->setText(State_LOCK_DISABLE_TEXT) ;
        ui->displayControlLabel_2->setText(State_LOCK_DISABLE_TEXT) ;
    }else{
        if(pcStatus.toppleControl){
           ui->displayControlLabel->setText(State_UNLOCK_TEXT) ;
           ui->displayControlLabel_2->setText(State_UNLOCK_TEXT) ;
        }else{
           ui->displayControlLabel->setText(State_LOCK_TEXT) ;
           ui->displayControlLabel_2->setText(State_LOCK_TEXT) ;
        }
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
        ui->manualStartButton->setEnabled(false);
        recordFlag = false;
        ui->recordStartButton->setText(Start_Record_TEXT);
        recorder->exit();
        ui->fileNameEdit->setEnabled(true);
        pcStatus.state  = false;
        ui->acctimelabel->setText("");
        acctimer->stop();
        if(startTimerFlag){
            startTimerFlag = false;
            ui->manualStartButton->setText(TIME_START_TEXT);
            ui->manualtimelabel->setText("");
            ui->timeEdit->setText("");
            timer->stop();
        }
    }else{
        QString fileName = ui->fileNameEdit->text();
        if(fileName.length() == 0){
            CusDialog cusdialog(Warning_NO_FILENAME_TEXT,1);
            cusdialog.exec();
            return;
        }
        pcStatus.state  = true;
        ui->manualStartButton->setEnabled(true);
        ui->fileNameEdit->setEnabled(false);
        recordFlag = true;
        ui->recordStartButton->setText(End_Record__TEXT);
        recorder->fileName = fileName;
        recorder->start();
        acctime.setHMS(0,0,0);
        acctimer->start();
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
        ui->manualStartButton->setText(TIME_START_TEXT);
        ui->manualtimelabel->setText("");
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
    if(recordFlag){
        CusDialog cusDialog("正在手动记录模式下，无法切换自动模式",1);
        cusDialog.exec();
        return;
    }
    if(autoStartFlag){
        warn_CusDialog = new  CusDialog("正在自动模式下，无法切换手动模式",1);
        warn_CusDialog->exec();
        delete warn_CusDialog;
        warn_CusDialog = NULL;
        return;
    }
    ui->stackedWidget->setCurrentIndex(0);
    ui->setButton->setEnabled(false);
    ui->manualButton->setEnabled(true);
    ui->autoButton->setEnabled(true);
    ui->infoButton->setEnabled(true);
}

void MainWindow::manualButtonClick()
{
    if(autoStartFlag){
        warn_CusDialog = new  CusDialog("正在自动模式下，无法切换手动模式",1);
        warn_CusDialog->exec();
        delete warn_CusDialog;
        warn_CusDialog = NULL;
        return;
    }
    ui->stackedWidget->setCurrentIndex(1);
    ui->setButton->setEnabled(true);
    ui->manualButton->setEnabled(false);
    ui->autoButton->setEnabled(true);
    ui->infoButton->setEnabled(true);
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
    if(recordFlag){
        CusDialog cusDialog("正在手动记录模式下，无法切换自动模式",1);
        cusDialog.exec();
        return;
    }
    if(autoStartFlag){
        warn_CusDialog = new  CusDialog("正在自动模式下，无法切换手动模式",1);
        warn_CusDialog->exec();
        delete warn_CusDialog;
        warn_CusDialog = NULL;
        return;
    }
    ui->stackedWidget->setCurrentIndex(3);
    ui->setButton->setEnabled(true);
    ui->manualButton->setEnabled(true);
    ui->autoButton->setEnabled(true);
    ui->infoButton->setEnabled(false);
}

void MainWindow::actionGroupButtonClick(int id)
{
    if(timer->isActive())
    {
        ui->manualtimelabel->setText("");
        startTimerFlag = false;
        ui->manualStartButton->setText(Start_TEXT);
        timer->stop();
    }
    if(recordFlag)
    {
       emit(recordStatus());
        if(id == manualAID)
        {
            AddDialog addAction;
            pcStatus.action = ActionAControl;
            pcStatus.actionState = ActionState_UNDO;
            int val = addAction.exec();
            if(val == 0)
            {
                qDebug()<<"ActionState_DONE";
                pcStatus.action = NOAction;
                pcStatus.actionState = ActionState_DONE;
                emit(recordStatus(addAction.content));
            }else if(val == -1)
            {
                qDebug()<<"ActionState_UNDO";
                pcStatus.action = NOAction;
                pcStatus.actionState = ActionState_UNDO;
                emit(recordStatus());
            }

        }else if(id == manualBID)
        {
            pcStatus.toppleControl = true;
            CusDialog cusdialog(ActionBControl_TEXT,0);
            pcStatus.action = ActionBControl;
            pcStatus.actionState = ActionState_UNDO;
            int val = cusdialog.exec();
            pcStatus.toppleControl = false;
            if(val == 0)
            {
                pcStatus.action = NOAction;
                pcStatus.actionState = ActionState_DONE;
            }else if(val == -1)
            {
                pcStatus.action = NOAction;
                pcStatus.actionState = ActionState_UNDO;
            }
            emit(recordStatus());
        }else if(id == manualCID)
        {
            CusDialog cusdialog(ActionCControl_TEXT,0);
            pcStatus.action = ActionCControl;
            pcStatus.actionState = ActionState_UNDO;
            int val = cusdialog.exec();
            if(val == 0)
            {
                pcStatus.action = NOAction;
                pcStatus.actionState = ActionState_DONE;
            }else if(val == -1)
            {
                pcStatus.action = NOAction;
                pcStatus.actionState = ActionState_UNDO;
            }
            emit(recordStatus());
        }else if(id == manualDID)
        {
            CusDialog cusdialog(ActionDControl_TEXT,0);
            pcStatus.action = ActionDControl;
            pcStatus.actionState = ActionState_UNDO;
            int val = cusdialog.exec();
            if(val == 0)
            {
                pcStatus.action = NOAction;
                pcStatus.actionState = ActionState_DONE;
            }else if(val == -1)
            {
                pcStatus.action = NOAction;
                pcStatus.actionState = ActionState_UNDO;
            }
            emit(recordStatus());
        }

    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

