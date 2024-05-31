#ifndef MAPWIDGET_H
#define MAPWIDGET_H

#include "widget.h"
#include "passenger.h"
#include "graph.h"

#include <QPainter>
#include <QPushButton>


class MapWidget : public QWidget
{
public:
    MapWidget(QWidget *);


protected:
    void paintEvent(QPaintEvent *event) override;
    void showEvent(QShowEvent *event) override;


private slots:

    void moveAlongPath();
    void updatePosition();
    int findClosestNode();

    void onMEIXIHUButtonClicked();
    void onHUIWANGButtonClicked();
    void onCSUOLDButtonClicked();

private:
    // 乘客类与图结构
    Passenger passenger;
    Graph graph;
    std::vector<QPointF> path; // 存储路径的成员变量

    // 地图中的按钮
    QPushButton *MEIXIHU_Button;
    QPushButton *HUIWANG_Button;
    QPushButton *CSU_OLD_Button;

    // 移动参数
    int currentSegment;
    int totalSegments;
    QTimer* moveTimer;
    int moveInterval;
    double speed;

};

#endif // MAPWIDGET_H
