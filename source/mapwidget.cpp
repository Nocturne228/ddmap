#include "mapwidget.h"

#define PEN_WIDTH 5



MapWidget::MapWidget(QWidget *parent) :
    // 根据乘客位置设置图标
    QWidget(parent), passenger(QPointF(CSU_X, CSU_Y+20), 0, ":/ultraman.ico"), graph()
{
    // 设置基础背景图片
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/csmap.png")));
    this->setPalette(palette);

}


void MapWidget::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);

    // 查找并连接按钮
    MEIXIHU_Button = findChild<QPushButton*>("MEIXIHU_Button");
    if (MEIXIHU_Button) {
        connect(MEIXIHU_Button, &QPushButton::clicked, this, &MapWidget::onMEIXIHUButtonClicked);
        qDebug() << "MEIXIHU_Button found and connected.";
    } else {
        qDebug() << "MEIXIHU_Button not found!";
    }
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
                QPointF midPoint((source.x() + target.x()) / 2, (source.y() + target.y()) / 2);
                painter.drawText(midPoint, QString::number(weight)); // 绘制权值
            }
        }
    }

    // 绘制出行路线的路径
        if (!path.empty()) {
            painter.setPen(QPen(Qt::red, 2)); // 红色线条表示路径，线条宽度为2
            for (size_t i = 1; i < path.size(); ++i) {
                painter.drawLine(path[i - 1], path[i]);
            }
        }

}


void MapWidget::onMEIXIHUButtonClicked()
{
    qDebug() << "Go to MEIXIHU";
    QPointF source = this->graph.getLocCor(0);
    QPointF target = this->graph.getLocCor(4);

    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;

    if (!path.empty()) {
            // 开始移动，设置定时器来更新乘客位置
            QTimer* moveTimer = new QTimer(this);
            connect(moveTimer, &QTimer::timeout, [=]() {
                if (!path.empty()) {
                    // 更新乘客位置为路径的下一个点
                    this->passenger.setPosition(path.front());
                    path.erase(path.begin());
                    update(); // 触发界面更新
                } else {
                    moveTimer->stop(); // 移动结束，停止定时器
                    delete moveTimer;
                }
            });
            moveTimer->start(1000); // 每秒更新一次位置
        }

    update();
}

