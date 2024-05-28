#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include "widget.h"
#include "passenger.h"
#include "graph.h"

#include <QPainter>


class MapWidget : public QWidget
{
public:
    MapWidget(QWidget *);

protected:
    void paintEvent(QPaintEvent *event) override;


private slots:

private:
    Passenger passenger;
    Graph graph;
};

#endif // MAPWIDGET_H
