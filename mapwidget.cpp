#include "mapwidget.h"




MapWidget::MapWidget(QWidget *parent) :
    QWidget(parent), passenger(QPointF(100, 100), 0, ":/ultraman.ico")
{
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/csmap.png")));
    this->setPalette(palette);


}


void MapWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿

    // 绘制乘客图标
    painter.drawPixmap(this->passenger.getPosition(), this->passenger.getIcon());

    // 绘制地点坐标点
        for (int i = 0; i < 10; ++i) { // 假设共有10个地点
            QPointF loc = getLocCor(i);
            painter.drawEllipse(loc, 5, 5); // 绘制圆形表示地点
            painter.drawText(loc.x() + 10, loc.y() + 10, QString::number(i)); // 绘制地点序号
        }
        // 绘制连接线
        painter.setPen(Qt::black);
        for (size_t i = 0; i <= 10; ++i) {
            painter.drawLine(getLocCor(i), getLocCor(i+1));
        }

}


// 获得图形中各个地点的位置
QPointF MapWidget::getLocCor(int location)
{
    int x, y;
    switch (location)
    {
    case 0: //中南大学
        x = CSU_X - MAP_X;
        y = CSU_Y - MAP_Y;
        break;
    case 1: //上海
        x = 807 - MAP_X;
        y = 498 - MAP_Y;
        break;
    case 2: //广州
        x = 686 -MAP_X;
        y = 668 -MAP_Y;
        break;
    case 3: //重庆
        x = 550 - MAP_X;
        y = 545 - MAP_Y;
        break;
    case 4: //青岛
        x = 758 - MAP_X;
        y = 390 - MAP_Y;
        break;
    case 5: //郑州
        x = 668 - MAP_X;
        y = 438 - MAP_Y;
        break;
    case 6: //兰州
        x = 503 - MAP_X;
        y = 422 - MAP_Y;
        break;
    case 7: //乌鲁木齐
        x = 232 - MAP_X;
        y = 255 - MAP_Y;
        break;
    case 8: //贵阳
        x = 565 - MAP_X;
        y = 610 - MAP_Y;
        break;
    case 9: //哈尔滨
        x = 826 - MAP_X;
        y = 150 - MAP_Y;
        break;
    }

    return QPointF(x, y);
}
