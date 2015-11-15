#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "capture.h"
#include <iostream>
#include <time.h>
#include <QMessageBox>
#include "FaceLogic.h"
#include "ReportWindow.h"
#include "Log.h"
#include <QDebug>

#include "cserialreader.h"
#include "cpredictor.h"
#include "cdatabase.h"

using namespace std;

bool MainWindow::initSeatDevice()
{
    qDebug() << "***Start initialize seat device";
    // the serial port & device part
    CSerialReader* p_iReader = CSerialReader::getReader();
    if(!p_iReader->OpenSerial())
    {
        qDebug() << "Cannot open serial port";
        return false;
    }
    qDebug() << "Open serial port succeed";

    if(!p_iReader->ConnectDevice())
    {
        qDebug() << "Cannot connect device";
        return false;
    }
    qDebug() << "Connect device succeed";

    // the predictor part, assume user test
    CPredictor* p_iPredictor = CPredictor::getPredictor("test");
    if (p_iPredictor == NULL)
    {
        qDebug() << "predictor initialize failed";
        return false;
    }
    qDebug() << "Predictor initalize succeed";

    qDebug() << "***Initialize seat device finished";

    return true;
}

bool MainWindow::seatProcess()
{
    qDebug() << "***Enter seatProcess";

    QString seatResultDisplayString = "";
    QString seatRawDataDisplayString = "";

    CSerialReader* p_iReader = CSerialReader::getReader();
    QList< QList<int> > iDataListList = p_iReader->ReadSerial();
    qDebug() << "iDataListList size" << iDataListList.size();

    CPredictor* p_iPredictor = CPredictor::getPredictor("test");
    for (int i = 0; i < iDataListList.size(); i++)
    {
        CPredictor::eSitType eRes = p_iPredictor->Predict(iDataListList.at(i));
        qDebug() << "Result" << i << eRes;
        seatResultDisplayString = seatResultDisplayString + "Result<" + QString::number(i) + "> " + QString::number(eRes) + " ";
        switch (eRes) {
        case CPredictor::NORMAL:
            seatResultDisplayString += "Normal";
            break;
        case CPredictor::LEFTWARD:
            seatResultDisplayString += "Leftward";
            break;
        case CPredictor::RIGHTWARD:
            seatResultDisplayString += "Rightward";
            break;
        case CPredictor::BACKWARD:
            seatResultDisplayString += "Backward";
            break;
        case CPredictor::FORWARD:
            seatResultDisplayString += "Forward";
        default:
            break;
        }
        seatResultDisplayString += "\n";
    }
    ui->seatInfoEdit->setPlainText(seatResultDisplayString);

    for (int i = 0; i < iDataListList.size(); i++)
    {
        seatRawDataDisplayString = seatRawDataDisplayString +  "<" + QString::number(i) + ">";
        for (int j = 0; j < 20; j++)
            seatRawDataDisplayString = seatRawDataDisplayString + "\t" + QString::number(iDataListList.at(i).at(j));
        seatRawDataDisplayString += "\n";
    }
    ui->seatRawDataEdit->setPlainText(seatRawDataDisplayString);

    qDebug() << "***Leave seatProcess";

    return true;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),timer(new QTimer)
{
    ui->setupUi(this);    
    connect(timer,SIGNAL(timeout()),this,SLOT(timing()));
    //ui->calendarWidget->setDateRange();

    if(!initSeatDevice()) qDebug() << "Initialize seat device failed";
    else qDebug() << "Initialize seat device succeed";
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

void MainWindow::shakeFrm()
{
        //记录窗体的初始位置
        QPoint p=this->pos();
        qsrand(time(NULL));

        //循环移动窗体位置,可以自己修改循环次数,次数越多,抖动时间越长
        for(int i=0;i<=50;i++)
        {
            //在窗体原来的位置的基础上随机改变窗体的坐标位置,其中的随机数区间可以随意修改,数值越大,抖动幅度越大,最好正负成对
            QPoint n =QPoint(p.x()+qrand()%20-10,p.y()+qrand()%20-10);
            this->move(n);
            //让窗体回到初始位置
            this->move(p);
        }
}

bool first =true;
int face_duration =0;
FacePostureType previous;
time_t start_t;
time_t end_t;
void MainWindow::timing()
{
    qDebug() << "***Enter timing***";
    ui->label->setPixmap(QPixmap::fromImage(detect()));
    if(first)
    {
        previous =FaceLogic::getRtType();
        first =false;
        start_t =time(NULL);
    }
    if(FaceLogic::getRtType() == previous)
    {
        face_duration++;
    }
    else
    {
        //以下为提交报告
        if(face_duration>=5)
        {
            end_t =time(NULL);
            tm* end_time =   localtime(&end_t);

            int hour =end_time->tm_hour;
            int min =end_time->tm_min;
            int sec =end_time->tm_sec;

            tm* start_time = localtime(&start_t);

            string startstr =int2str(start_time->tm_hour)+":"+
                             int2str(start_time->tm_min)+":"+
                             int2str(start_time->tm_sec);
            string endstr =  int2str(hour)+":"+
                             int2str(min)+":"+
                             int2str(sec);
            int duration =3600*(hour-start_time->tm_hour)+
                          60*(min-start_time->tm_min)+
                          (sec-start_time->tm_sec);


            extern const char * PostureEnumNames[];
            Report report(startstr,endstr,string(PostureEnumNames[previous]),duration);
            string day_str =int2str(1900 + start_time->tm_year)+"-"+
                            int2str(1 + start_time->tm_mon/*此month的范围为0-11*/)+"-"+
                            int2str(start_time->tm_mday);


            writeReport(report,day_str.c_str());

        }

        previous =FaceLogic::getRtType();
        face_duration =1;
        start_t =time(NULL);
    }

    //如果同一姿势超过五次，则按姿势相应处理
    if(face_duration>=5)
    {
        switch(FaceLogic::getRtType())
        {
           case Profile:
              ui->statusBar->showMessage("you are tilting your face too long!", 1000);
              break;

           case NO_FACE:
              ui->statusBar->showMessage("you have left the computer...", 1000);
              shakeFrm();
           //其他的待会再加
           case Normal:
              if(face_duration>=60)
              {
                ui->statusBar->showMessage("hold on,you have good posture for a minute!",2000);
              }
                break;
           default:
                break;
        }
    }
    ui->plainTextEdit->setPlainText(QString(FaceLogic::fetchJudgedMessage().c_str()));

    seatProcess();

    qDebug() << "***Leave timing***";
}

void MainWindow::on_MainWindow_destroyed()
{
     exitApp();
}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{

    string str =int2str(date.year())+"-"+
                int2str(date.month())+"-"+
                int2str(date.day());
    vector<Report> reportSet =getReportByDay(str.c_str());
    ReportWindow* w =new ReportWindow(this,reportSet);
    w->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    qDebug() << "Button4 clicked";
    if(ui->pushButton_4->text()=="Start")
    {
        if(!isAllowCameraOpen())
        {
            QMessageBox::StandardButton bt =QMessageBox::information(this,"open Camera",tr("this application requests to open your camera,do you agree?"),QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            if(bt==QMessageBox::No)
                return;
            allowCameraOpen();
        }
        string msg = openCamera();
        qDebug() << msg.data();

        //定时截屏
        qDebug() << "Start timer";
        timer->start(1000);
        ui->pushButton_4->setText("Stop");
    }
    else
    {
        qDebug() << "Stop timer";
        timer->stop();
        ui->pushButton_4->setText("Start");
    }
}
