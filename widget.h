#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>

#include <QIcon>
#include <QTimer>
#include <QThread>



namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


private:
    Ui::Widget *ui;

    // 参与时间进程的变量
    QTimer *mstimer;
    QThread *timethread;


    void Initial_UI();
    void Initial_Time_Thread();


private slots:


signals:
};






#endif // WIDGET_H
