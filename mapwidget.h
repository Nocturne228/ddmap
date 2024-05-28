#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#define MAP_X 0
#define MAP_Y 0

#define CSU_X 570
#define CSU_Y 516

#include "widget.h"
#include "passenger.h"

#include <QPainter>


class MapWidget : public QWidget
{
public:
    MapWidget(QWidget *);

    QPointF getLocCor(int location);//获得地点对应坐标

protected:
    void paintEvent(QPaintEvent *event) override;


private slots:

private:
    Passenger passenger;
};

#endif // MAPWIDGET_H
