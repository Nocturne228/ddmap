#include "mapwidget.h"

#define PEN_WIDTH 5

MapWidget::MapWidget(QWidget *parent) :
    // 根据乘客位置设置图标
    QWidget(parent), passenger(QPointF(CSU_X, CSU_Y+20), 0, ":/ultraman.ico"),
    driver(QPointF(CSUFT_X, CSUFT_Y+20), 0, ":/car.ico"), graph(),
    currentSegment(0), totalSegments(0), moveTimer(nullptr), moveInterval(20), speed(10)

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
    // 中南校本部
    CSU_OLD_Button = findChild<QPushButton*>("CSU_OLD_Button");
    if (CSU_OLD_Button) {
        CSU_OLD_Button->setIcon(QIcon(":/loc.ico"));
        connect(CSU_OLD_Button, &QPushButton::clicked, this, &MapWidget::onCSUOLDButtonClicked);
        qDebug() << "CSU_OLD_Button found and connected.";
    } else {
        qDebug() << "CSU_OLD_Button not found!";
    }
    // 梅溪湖
    MEIXIHU_Button = findChild<QPushButton*>("MEIXIHU_Button");
    if (MEIXIHU_Button) {
        MEIXIHU_Button->setIcon(QIcon(":/loc.ico"));
        connect(MEIXIHU_Button, &QPushButton::clicked, this, &MapWidget::onMEIXIHUButtonClicked);
        qDebug() << "MEIXIHU_Button found and connected.";
    } else {
        qDebug() << "MEIXIHU_Button not found!";
    }
    // 回望书店
    HUIWANG_Button = findChild<QPushButton*>("HUIWANG_Button");
    if (HUIWANG_Button) {
        HUIWANG_Button->setIcon(QIcon(":/loc.ico"));
        connect(HUIWANG_Button, &QPushButton::clicked, this, &MapWidget::onHUIWANGButtonClicked);
        qDebug() << "HUIWANG_Button found and connected.";
    } else {
        qDebug() << "HUIWANG_Button not found!";
    }

    CSU_Button = findChild<QPushButton*>("CSU_Button");
        if (CSU_Button) {
            CSU_Button->setIcon(QIcon(":/loc.ico"));
            connect(CSU_Button, &QPushButton::clicked, this, &MapWidget::onCSUButtonClicked);
            qDebug() << "CSU_Button found and connected.";
        } else {
            qDebug() << "CSU_Button not found!";
        }

        HNU_Button = findChild<QPushButton*>("HNU_Button");
        if (HNU_Button) {
            HNU_Button->setIcon(QIcon(":/loc.ico"));
            connect(HNU_Button, &QPushButton::clicked, this, &MapWidget::onHNUButtonClicked);
            qDebug() << "HNU_Button found and connected.";
        } else {
            qDebug() << "HNU_Button not found!";
        }

        XIANGBIWO_Button = findChild<QPushButton*>("XIANGBIWO_Button");
        if (XIANGBIWO_Button) {
            XIANGBIWO_Button->setIcon(QIcon(":/loc.ico"));
            connect(XIANGBIWO_Button, &QPushButton::clicked, this, &MapWidget::onXIANGBIWOButtonClicked);
            qDebug() << "XIANGBIWO_Button found and connected.";
        } else {
            qDebug() << "XIANGBIWO_Button not found!";
        }

        YANGHU_Button = findChild<QPushButton*>("YANGHU_Button");
        if (YANGHU_Button) {
            YANGHU_Button->setIcon(QIcon(":/loc.ico"));
            connect(YANGHU_Button, &QPushButton::clicked, this, &MapWidget::onYANGHUButtonClicked);
            qDebug() << "YANGHU_Button found and connected.";
        } else {
            qDebug() << "YANGHU_Button not found!";
        }

        WUYI_Button = findChild<QPushButton*>("WUYI_Button");
        if (WUYI_Button) {
            WUYI_Button->setIcon(QIcon(":/loc.ico"));
            connect(WUYI_Button, &QPushButton::clicked, this, &MapWidget::onWUYIButtonClicked);
            qDebug() << "WUYI_Button found and connected.";
        } else {
            qDebug() << "WUYI_Button not found!";
        }

        HNNU_Button = findChild<QPushButton*>("HNNU_Button");
        if (HNNU_Button) {
            HNNU_Button->setIcon(QIcon(":/loc.ico"));
            connect(HNNU_Button, &QPushButton::clicked, this, &MapWidget::onHNNUButtonClicked);
            qDebug() << "HNNU_Button found and connected.";
        } else {
            qDebug() << "HNNU_Button not found!";
        }

        BISHAHU_Button = findChild<QPushButton*>("BISHAHU_Button");
        if (BISHAHU_Button) {
            BISHAHU_Button->setIcon(QIcon(":/loc.ico"));
            connect(BISHAHU_Button, &QPushButton::clicked, this, &MapWidget::onBISHAHUButtonClicked);
            qDebug() << "BISHAHU_Button found and connected.";
        } else {
            qDebug() << "BISHAHU_Button not found!";
        }

        CSUST_Button = findChild<QPushButton*>("CSUST_Button");
        if (CSUST_Button) {
            CSUST_Button->setIcon(QIcon(":/loc.ico"));
            connect(CSUST_Button, &QPushButton::clicked, this, &MapWidget::onCSUSTButtonClicked);
            qDebug() << "CSUST_Button found and connected.";
        } else {
            qDebug() << "CSUST_Button not found!";
        }

        XIANGYA_Button = findChild<QPushButton*>("XIANGYA_Button");
        if (XIANGYA_Button) {
            XIANGYA_Button->setIcon(QIcon(":/loc.ico"));
            connect(XIANGYA_Button, &QPushButton::clicked, this, &MapWidget::onXIANGYAButtonClicked);
            qDebug() << "XIANGYA_Button found and connected.";
        } else {
            qDebug() << "XIANGYA_Button not found!";
        }

        NANJIAO_Button = findChild<QPushButton*>("NANJIAO_Button");
        if (NANJIAO_Button) {
            NANJIAO_Button->setIcon(QIcon(":/loc.ico"));
            connect(NANJIAO_Button, &QPushButton::clicked, this, &MapWidget::onNANJIAOButtonClicked);
            qDebug() << "NANJIAO_Button found and connected.";
        } else {
            qDebug() << "NANJIAO_Button not found!";
        }

        CSUFT_Button = findChild<QPushButton*>("CSUFT_Button");
        if (CSUFT_Button) {
            CSUFT_Button->setIcon(QIcon(":/loc.ico"));
            connect(CSUFT_Button, &QPushButton::clicked, this, &MapWidget::onCSUFTButtonClicked);
            qDebug() << "CSUFT_Button found and connected.";
        } else {
            qDebug() << "CSUFT_Button not found!";
        }

        StartMove_Button = findChild<QPushButton*>("StartMove_Button");
        if (StartMove_Button) {
            StartMove_Button->setIcon(QIcon(":/loc.ico"));
            connect(StartMove_Button, &QPushButton::clicked, this, &MapWidget::onStartMoveButtonClicked);
            qDebug() << "StartMove_Button found and connected.";
        } else {
            qDebug() << "StartMove_Button not found!";
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
    painter.drawPixmap(this->driver.getPosition(), this->driver.getIcon());

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

// 去梅溪湖
void MapWidget::onMEIXIHUButtonClicked()
{
    qDebug() << "Go to MEIXIHU";
    qDebug() << "Passenger is at location" << findClosestNode();
    int currPosition = findClosestNode();
    QPointF source = this->graph.getLocCor(currPosition);
    QPointF target = this->graph.getLocCor(4);

    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;
}


// 去回望书店
void MapWidget::onHUIWANGButtonClicked()
{
    qDebug() << "Go to MEIXIHU";
    qDebug() << "Passenger is at location" << findClosestNode();
    int currPosition = findClosestNode();
    QPointF source = this->graph.getLocCor(currPosition);
    QPointF target = this->graph.getLocCor(2);

    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;
}

// 去校本部
void MapWidget::onCSUOLDButtonClicked()
{
    qDebug() << "Go to CSU_Old";
    qDebug() << "Passenger is at location" << findClosestNode();
    int currPosition = findClosestNode();
    QPointF source = this->graph.getLocCor(currPosition);
    QPointF target = this->graph.getLocCor(1);

    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;
}

void MapWidget::onCSUButtonClicked() {
    int currPosition = findClosestNode();
    QPointF source = this->graph.getLocCor(currPosition);
    QPointF target = this->graph.getLocCor(0);
    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;
}

void MapWidget::onHNUButtonClicked() {
    int currPosition = findClosestNode();
    QPointF source = this->graph.getLocCor(currPosition);
    QPointF target = this->graph.getLocCor(3);
    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;
}

// 继续添加其他槽函数...

void MapWidget::onXIANGBIWOButtonClicked() {
    int currPosition = findClosestNode();
    QPointF source = this->graph.getLocCor(currPosition);
    QPointF target = this->graph.getLocCor(5);
    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;
}

void MapWidget::onYANGHUButtonClicked() {
    int currPosition = findClosestNode();
    QPointF source = this->graph.getLocCor(currPosition);
    QPointF target = this->graph.getLocCor(7);
    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;
}

void MapWidget::onWUYIButtonClicked() {
    int currPosition = findClosestNode();
    QPointF source = this->graph.getLocCor(currPosition);
    QPointF target = this->graph.getLocCor(11);
    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;
}

void MapWidget::onHNNUButtonClicked() {
    int currPosition = findClosestNode();
    QPointF source = this->graph.getLocCor(currPosition);
    QPointF target = this->graph.getLocCor(6);
    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;
}

void MapWidget::onBISHAHUButtonClicked() {
    int currPosition = findClosestNode();
    QPointF source = this->graph.getLocCor(currPosition);
    QPointF target = this->graph.getLocCor(10);
    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;
}

void MapWidget::onCSUSTButtonClicked() {
    int currPosition = findClosestNode();
    QPointF source = this->graph.getLocCor(currPosition);
    QPointF target = this->graph.getLocCor(9);
    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;
}

void MapWidget::onXIANGYAButtonClicked() {
    int currPosition = findClosestNode();
    QPointF source = this->graph.getLocCor(currPosition);
    QPointF target = this->graph.getLocCor(13);
    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;
}

void MapWidget::onNANJIAOButtonClicked() {
    int currPosition = findClosestNode();
    QPointF source = this->graph.getLocCor(currPosition);
    QPointF target = this->graph.getLocCor(8);
    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;
}

void MapWidget::onCSUFTButtonClicked() {
    int currPosition = findClosestNode();
    QPointF source = this->graph.getLocCor(currPosition);
    QPointF target = this->graph.getLocCor(12);
    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;
}


void MapWidget::onStartMoveButtonClicked() {
    qDebug() << "Start Move";
    qDebug() << "Total weight in mapwidget: " << graph.getTotalWeight();
    if (!path.empty()) {
        moveAlongPath();
    }
    update();
}


// 沿paths路径移动
void MapWidget::moveAlongPath()
{
    qDebug() << "Path size:" << path.size();
    currentSegment = 0;
    totalSegments = path.size() - 1;

    if (moveTimer) {
        moveTimer->stop();
        delete moveTimer;
    }

    moveTimer = new QTimer(this);
    connect(moveTimer, &QTimer::timeout, this, &MapWidget::updatePosition);
    moveTimer->start(moveInterval);
}

void MapWidget::updatePosition()
{
    if (currentSegment < totalSegments) {
        QPointF currentPos = passenger.getPosition();
        QPointF nextPos = path[currentSegment + 1];
        double distance = std::hypot(nextPos.x() - currentPos.x(), nextPos.y() - currentPos.y());

        if (distance > speed) {
            double ratio = speed / distance;
            QPointF moveStep((nextPos.x() - currentPos.x()) * ratio, (nextPos.y() - currentPos.y()) * ratio);
            passenger.setPosition(currentPos + moveStep);
        } else {
            passenger.setPosition(nextPos);
            ++currentSegment;
        }

        update();
    } else {
        moveTimer->stop();
        moveTimer->deleteLater();
        moveTimer = nullptr;
    }
}

// 查询距离最近的节点，找到对应的graph中的节点坐标
int MapWidget::findClosestNode() {
    QPointF passengerPos = passenger.getPosition();
    double minDistance = std::numeric_limits<double>::max();
    int closestNode = -1;

    for (int i = 0; i < graph.getMaxNode(); ++i) {
        QPointF nodePos = graph.getLoc(i);
        double distance = std::hypot(nodePos.x() - passengerPos.x(), nodePos.y() - passengerPos.y());

        if (distance < minDistance) {
            minDistance = distance;
            closestNode = i;
        }
    }

    return closestNode;
}
