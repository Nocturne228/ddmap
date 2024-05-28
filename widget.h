#ifndef WIDGET_H
#define WIDGET_H

#include "mapwidget.h"

#include <QMainWindow>
#include <QWidget>
#include <QDebug>

#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QString>
#include <QMessageBox>

#include <QDate>
#include <QTime>
#include <QDateTimeEdit>
#include <QTimer>
#include <QThread>
#include <QKeyEvent>
#include <QEvent>

#include <QPixmap>
#include <QScrollArea>
#include <QPalette>
#include <QLayout>
#include <QPalette>


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


    void Initial_UI();


private slots:


signals:
};






#endif // WIDGET_H
