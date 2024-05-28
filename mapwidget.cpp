#include "mapwidget.h"

#define PEN_WIDTH 5



MapWidget::MapWidget(QWidget *parent) :
    QWidget(parent), passenger(QPointF(100, 100), 0, ":/ultraman.ico"), graph()
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

    // 设置画笔
    QPen pen(Qt::black);
    pen.setWidth(PEN_WIDTH); // 设置宽度
    painter.setPen(pen);

    // 绘制乘客图标
    painter.drawPixmap(this->passenger.getPosition(), this->passenger.getIcon());

    // 绘制地点坐标点
    for (int i = 0; i < graph.getMaxNode(); ++i) { // 假设共有10个地点
        QPointF loc = this->graph.getLoc(i);
        painter.drawEllipse(loc, 5, 5); // 绘制圆形表示地点
        painter.drawText(loc.x() + 10, loc.y() + 10, QString::number(i)); // 绘制地点序号
    }


    // 绘制连接线

    for (int i = 0; i < this->graph.getMaxNode(); ++i) {
        for (int j = i + 1; j < this->graph.getMaxNode(); ++j) { // 只处理上三角矩阵，避免重复
            int weight = this->graph.getWeight(i, j);
            if (weight != std::numeric_limits<int>::max()) {
                QPointF source = this->graph.getLocCor(i);
                QPointF target = this->graph.getLocCor(j);
                painter.drawLine(source, target); // 绘制边

                // 计算边的中点位置
//                QPointF midPoint((source.x() + target.x()) / 2, (source.y() + target.y()) / 2);
//                painter.drawText(midPoint, QString::number(weight)); // 绘制权值
            }
        }
    }

}

