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
//    void Button4Clicked();

    void on_CSU_Button_clicked();
    void on_XIANGYA_Button_clicked();


    void on_StartButton_clicked();

signals:
};






#endif // WIDGET_H
