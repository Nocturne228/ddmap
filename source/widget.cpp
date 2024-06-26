#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent), ui(new Ui::Widget), graph()
{
    ui->setupUi(this);
    Initial_UI(); // 初始化界面
    Initial_Signal_Slot(); // 初始化信号槽
}


//初始化图形界面
void Widget::Initial_UI()
{
    qDebug() << "Successfully initialize UI";
    this->setFixedSize(1280, 820);//设置窗口大小
    this->setWindowTitle("滴滴出行");//设置窗口标题
    QIcon exe_ico(":/appicon.ico");
    this->setWindowIcon(exe_ico);//设置窗口图标

    // 添加出发时间(不可编辑)
    ui->StartTimeEdit->setTime(QTime::currentTime());

    ui->CallCarButton->setIcon(QIcon(":/callcar.ico"));
    ui->StartButton->setIcon(QIcon(":/go.ico"));

    ui->StartButton->setEnabled(false);

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

void Widget::Initial_Signal_Slot()
{
}

void Widget::on_CSU_Button_clicked()
{
    qDebug() << "CSU Button Clicked";
    // 获取当前时间
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // 将时间转换为字符串
    QString timeString = currentDateTime.toString("hh:mm:ss");

}

void Widget::on_XIANGYA_Button_clicked()
{
    qDebug() << "XIANGYA Button Clicked";
}


void Widget::on_StartButton_clicked()
{
    ui->StartMove_Button->click();
    ui->CostNumber->display(ui->CostNumber_map->value()/30);
    ui->DistanceLabel->setText(ui->Dis_Laebl->text());
    ui->TimeLabel->setText(ui->Time_Label->text());
    ui->TargetLabel->setText(ui->Loc_Label->text());
}

void Widget::on_CallCarButton_clicked()
{
    ui->CallCar_Button->click();
    ui->DistanceLabel->setText(ui->Dis_Laebl->text());
    ui->TimeLabel->setText(ui->Time_Label->text());

    ui->StartButton->setEnabled(true);
}

void Widget::on_ResetButton_clicked()
{
    ui->StartButton->setEnabled(false);
    ui->ResetPos_Button->click();
}
