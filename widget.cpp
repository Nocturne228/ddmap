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

}


//退出图形界面
Widget::~Widget()
{

    delete ui;
}
