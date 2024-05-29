#ifndef WIDGET_H
#define WIDGET_H

#include "graph.h"

#include <QWidget>
#include <QDebug>

#include <QIcon>
#include <QTimer>
#include <QThread>
#include <QPushButton>



namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();


private:
    Ui::Widget *ui;

    // 参与时间进程的变量
    QTimer *mstimer;
    QThread *timethread;
    Graph graph;


    void Initial_UI();
    void Initial_Time_Thread();
    void Initial_Signal_Slot();


private slots:
    void startButtonClicked();//开始按钮按下，开始计算路径图形输出
//    void Button4Clicked();

signals:
};






#endif // WIDGET_H
