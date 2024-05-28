#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    Initial_UI();//初始化界面
}


//初始化图形界面
void Widget::Initial_UI()
{
    qDebug() << "Successfully initialize UI";
    this->setFixedSize(1280, 820);//设置窗口大小
    this->setWindowTitle("滴滴出行");//设置窗口标题
    QIcon exe_ico(":/exe.ico");
    this->setWindowIcon(exe_ico);//设置窗口图标

    // 添加出发时间(不可编辑)
    ui->StartDateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->StartDateTimeEdit->setEnabled(false);
}


//退出图形界面
Widget::~Widget()
{
    qDebug() << "Successfully exit.";
    delete ui;
}


//添加计时所用的线程和timer以确保时间计算的准确
void Widget::Initial_Time_Thread()
{
    //计时功能及所需的线程
    mstimer = new QTimer;
    mstimer->setInterval(1);

    timethread = new QThread();
    timethread->start();

    mstimer->moveToThread(timethread);
}

