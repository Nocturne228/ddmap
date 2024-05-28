#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 使用样式表设置背景图像
    QString filename(":/new/prefix1/map.png");
    QImage* img=new QImage;
    img->load(filename);
    }

MainWindow::~MainWindow()
{
    delete ui;
}
