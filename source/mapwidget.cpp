#include "mapwidget.h"
#define PASSENGER 0
#define DRIVER 1
#define PEN_WIDTH 5

MapWidget::MapWidget(QWidget *parent) :
    // 根据乘客位置设置图标
    QWidget(parent), passenger(QPointF(CSU_X, CSU_Y+20), 0, ":/ultraman.ico"),
    driver(QPointF(CSUFT_X, CSUFT_Y), 0, ":/car.ico"), graph(),
    currentSegment(0), totalSegments(0), moveTimer(nullptr), moveInterval(20), speed(10),
    driver1(QPointF(MEIXIHU_X, MEIXIHU_Y), 0, ":/car.ico"),
    driver2(QPointF(HNNU_X, HNNU_Y), 0, ":/car.ico")
{
    // 设置基础背景图片
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/csmap.png")));
    this->setPalette(palette);

    driver.setState(0);
    driver1.setState(1);
    driver2.setState(2);
    passenger.setIsVisible(true);
}

void MapWidget::showEvent(QShowEvent *event) {
    QWidget::showEvent(event);

    // 查找并连接按钮
    // 中南校本部
    CSU_OLD_Button = findChild<QPushButton*>("CSU_OLD_Button");
    CSU_OLD_Button->setIcon(QIcon(":/loc.ico"));
    connect(CSU_OLD_Button, &QPushButton::clicked, this, &MapWidget::onCSUOLDButtonClicked);
    // 梅溪湖
    MEIXIHU_Button = findChild<QPushButton*>("MEIXIHU_Button");
    MEIXIHU_Button->setIcon(QIcon(":/loc.ico"));
    connect(MEIXIHU_Button, &QPushButton::clicked, this, &MapWidget::onMEIXIHUButtonClicked);
    // 回望书店
    HUIWANG_Button = findChild<QPushButton*>("HUIWANG_Button");
    HUIWANG_Button->setIcon(QIcon(":/loc.ico"));
    connect(HUIWANG_Button, &QPushButton::clicked, this, &MapWidget::onHUIWANGButtonClicked);

    CSU_Button = findChild<QPushButton*>("CSU_Button");
    CSU_Button->setIcon(QIcon(":/loc.ico"));
    connect(CSU_Button, &QPushButton::clicked, this, &MapWidget::onCSUButtonClicked);

    HNU_Button = findChild<QPushButton*>("HNU_Button");
    HNU_Button->setIcon(QIcon(":/loc.ico"));
    connect(HNU_Button, &QPushButton::clicked, this, &MapWidget::onHNUButtonClicked);

    XIANGBIWO_Button = findChild<QPushButton*>("XIANGBIWO_Button");
    XIANGBIWO_Button->setIcon(QIcon(":/loc.ico"));
    connect(XIANGBIWO_Button, &QPushButton::clicked, this, &MapWidget::onXIANGBIWOButtonClicked);

    YANGHU_Button = findChild<QPushButton*>("YANGHU_Button");
    YANGHU_Button->setIcon(QIcon(":/loc.ico"));
    connect(YANGHU_Button, &QPushButton::clicked, this, &MapWidget::onYANGHUButtonClicked);

    WUYI_Button = findChild<QPushButton*>("WUYI_Button");
    WUYI_Button->setIcon(QIcon(":/loc.ico"));
    connect(WUYI_Button, &QPushButton::clicked, this, &MapWidget::onWUYIButtonClicked);

    HNNU_Button = findChild<QPushButton*>("HNNU_Button");
    HNNU_Button->setIcon(QIcon(":/loc.ico"));
    connect(HNNU_Button, &QPushButton::clicked, this, &MapWidget::onHNNUButtonClicked);

    BISHAHU_Button = findChild<QPushButton*>("BISHAHU_Button");
    BISHAHU_Button->setIcon(QIcon(":/loc.ico"));
    connect(BISHAHU_Button, &QPushButton::clicked, this, &MapWidget::onBISHAHUButtonClicked);

    CSUST_Button = findChild<QPushButton*>("CSUST_Button");
    CSUST_Button->setIcon(QIcon(":/loc.ico"));
    connect(CSUST_Button, &QPushButton::clicked, this, &MapWidget::onCSUSTButtonClicked);

    XIANGYA_Button = findChild<QPushButton*>("XIANGYA_Button");
    XIANGYA_Button->setIcon(QIcon(":/loc.ico"));
    connect(XIANGYA_Button, &QPushButton::clicked, this, &MapWidget::onXIANGYAButtonClicked);

    NANJIAO_Button = findChild<QPushButton*>("NANJIAO_Button");
    NANJIAO_Button->setIcon(QIcon(":/loc.ico"));
    connect(NANJIAO_Button, &QPushButton::clicked, this, &MapWidget::onNANJIAOButtonClicked);

    CSUFT_Button = findChild<QPushButton*>("CSUFT_Button");
    CSUFT_Button->setIcon(QIcon(":/loc.ico"));
    connect(CSUFT_Button, &QPushButton::clicked, this, &MapWidget::onCSUFTButtonClicked);


    StartMove_Button = findChild<QPushButton*>("StartMove_Button");
    StartMove_Button->setVisible(false);
    StartMove_Button->setIcon(QIcon(":/loc.ico"));
    connect(StartMove_Button, &QPushButton::clicked, this, &MapWidget::onStartMoveButtonClicked);

    CostNumber_MAP = findChild<QLCDNumber*>("CostNumber_map");
//    CostNumber_MAP->setVisible(false);

    CallCar_Button = findChild<QPushButton*>("CallCar_Button");
    connect(CallCar_Button, &QPushButton::clicked, this, &MapWidget::onCallCarButtonClicked);

    ResetPos_Button = findChild<QPushButton*>("ResetPos_Button");
    connect(ResetPos_Button, &QPushButton::clicked, this, &MapWidget::onResetPosButtonClicked);
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
    if (passenger.getIsVisible()) {
        painter.drawPixmap(this->passenger.getPosition(), this->passenger.getIcon());
    }
    painter.drawPixmap(this->driver.getPosition(), this->driver.getIcon());
    painter.drawPixmap(this->driver1.getPosition(), this->driver.getIcon());
    painter.drawPixmap(this->driver2.getPosition(), this->driver.getIcon());

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
    if (!path.empty() && isMoving == 1) {
        painter.setPen(QPen(Qt::red, 2)); // 红色线条表示路径，线条宽度为2
        for (size_t i = 1; i < path.size(); ++i) {
            painter.drawLine(path[i - 1], path[i]);
        }
    }

    if (!isMoving) {
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
    }
}

// 去梅溪湖
void MapWidget::onMEIXIHUButtonClicked()
{
    int currPosition = findClosestNode(passenger);
    QPointF source = this->graph.getLocCor(currPosition);
    QPointF target = this->graph.getLocCor(4);

    CostNumber_MAP->display(this->graph.getShortestPathWeight(currPosition, 4));

    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;

}


// 去回望书店
void MapWidget::onHUIWANGButtonClicked()
{
    int currPosition = findClosestNode(passenger);
    QPointF source = this->graph.getLocCor(currPosition);
    QPointF target = this->graph.getLocCor(2);

    CostNumber_MAP->display(this->graph.getShortestPathWeight(currPosition, 2));

    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;
}

// 去校本部
void MapWidget::onCSUOLDButtonClicked()
{
    int currPosition = findClosestNode(passenger);
    QPointF source = this->graph.getLocCor(currPosition);
    QPointF target = this->graph.getLocCor(1);

    CostNumber_MAP->display(this->graph.getShortestPathWeight(currPosition, 1));

    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;
}

void MapWidget::onCSUButtonClicked() {
    int currPosition = findClosestNode(passenger);
    QPointF source = this->graph.getLocCor(currPosition);
    QPointF target = this->graph.getLocCor(0);

    CostNumber_MAP->display(this->graph.getShortestPathWeight(currPosition, 0));

    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;
}

void MapWidget::onHNUButtonClicked() {
    int currPosition = findClosestNode(passenger);
    QPointF source = this->graph.getLocCor(currPosition);
    QPointF target = this->graph.getLocCor(3);

    CostNumber_MAP->display(this->graph.getShortestPathWeight(currPosition, 3));

    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;
}

// 继续添加其他槽函数...

void MapWidget::onXIANGBIWOButtonClicked() {
    int currPosition = findClosestNode(passenger);
    QPointF source = this->graph.getLocCor(currPosition);
    QPointF target = this->graph.getLocCor(5);

    CostNumber_MAP->display(this->graph.getShortestPathWeight(currPosition, 5));

    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;
}

void MapWidget::onYANGHUButtonClicked() {
    int currPosition = findClosestNode(passenger);
    QPointF source = this->graph.getLocCor(currPosition);
    QPointF target = this->graph.getLocCor(7);

    CostNumber_MAP->display(this->graph.getShortestPathWeight(currPosition, 7));

    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;
}

void MapWidget::onWUYIButtonClicked() {
    int currPosition = findClosestNode(passenger);
    QPointF source = this->graph.getLocCor(currPosition);
    QPointF target = this->graph.getLocCor(11);

    CostNumber_MAP->display(this->graph.getShortestPathWeight(currPosition, 11));

    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;
}

void MapWidget::onHNNUButtonClicked() {
    int currPosition = findClosestNode(passenger);
    QPointF source = this->graph.getLocCor(currPosition);
    QPointF target = this->graph.getLocCor(6);

    CostNumber_MAP->display(this->graph.getShortestPathWeight(currPosition, 6));

    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;
}

void MapWidget::onBISHAHUButtonClicked() {
    int currPosition = findClosestNode(passenger);
    QPointF source = this->graph.getLocCor(currPosition);
    QPointF target = this->graph.getLocCor(10);

    CostNumber_MAP->display(this->graph.getShortestPathWeight(currPosition, 10));

    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;
}

void MapWidget::onCSUSTButtonClicked() {
    int currPosition = findClosestNode(passenger);
    QPointF source = this->graph.getLocCor(currPosition);
    QPointF target = this->graph.getLocCor(9);

    CostNumber_MAP->display(this->graph.getShortestPathWeight(currPosition, 9));

    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;
}

void MapWidget::onXIANGYAButtonClicked() {
    int currPosition = findClosestNode(passenger);
    QPointF source = this->graph.getLocCor(currPosition);
    QPointF target = this->graph.getLocCor(13);

    CostNumber_MAP->display(this->graph.getShortestPathWeight(currPosition, 13));

    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;
}

void MapWidget::onNANJIAOButtonClicked() {
    int currPosition = findClosestNode(passenger);
    QPointF source = this->graph.getLocCor(currPosition);
    QPointF target = this->graph.getLocCor(8);

    CostNumber_MAP->display(this->graph.getShortestPathWeight(currPosition, 8));

    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;
}

void MapWidget::onCSUFTButtonClicked() {
    int currPosition = findClosestNode(passenger);
    QPointF source = this->graph.getLocCor(currPosition);
    QPointF target = this->graph.getLocCor(12);

    CostNumber_MAP->display(this->graph.getShortestPathWeight(currPosition, 12));

    std::vector<QPointF> paths = this->graph.dijkstra(source, target);
    path = paths;
}




void MapWidget::onStartMoveButtonClicked() {
    this->state = PASSENGER;
    qDebug() << "Start Move";
    qDebug() << "Total weight in mapwidget: " << graph.getTotalWeight();
    if (!path.empty()) {
        moveAlongPath();
        setAllButtonsEnabled(false); // 禁用按钮
        isMoving = 1;
    }
    update();
}

void MapWidget::onCallCarButtonClicked()
{
    this->currDriver = findNearestDriver();
    this->state = DRIVER;
    int currP = findClosestNode(passenger);
    int currD = 0;
    switch(currDriver) {
    case 0:
        currD = findClosestNode(driver);
        break;
    case 1:
        currD = findClosestNode(driver1);
        break;
    case 2:
        currD = findClosestNode(driver2);
        break;

    }
    std::vector<QPointF> paths = graph.dijkstra(graph.getLocCor(currD), graph.getLocCor(currP));
    drivePath = paths;

    qDebug() << "Car is moving";
    if (!drivePath.empty()) {
        moveAlongPath();
        setAllButtonsEnabled(false); // 禁用按钮
        isMoving = 1;
    }
    update();
}

void MapWidget::onResetPosButtonClicked()
{
    QPointF newPost = getRandomLocation();
    passenger.setPosition(newPost);
    update();
}


// 沿paths路径移动
void MapWidget::moveAlongPath()
{
    currentSegment = 0;
    if (this->state) {
        totalSegments = drivePath.size() - 1;
    } else {
        totalSegments = path.size() - 1;
    }
//    totalSegments = path.size() - 1;

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
    if (this->state) {
        switch (currDriver) {
        case 0:
            if (currentSegment < totalSegments) {

                QPointF currentPos = driver.getPosition();
                QPointF nextPos = drivePath[currentSegment + 1];
                double distance = std::hypot(nextPos.x() - currentPos.x(), nextPos.y() - currentPos.y());

                if (distance > speed) {
                    double ratio = speed / distance;
                    QPointF moveStep((nextPos.x() - currentPos.x()) * ratio, (nextPos.y() - currentPos.y()) * ratio);
                    driver.setPosition(currentPos + moveStep);
                } else {
                    driver.setPosition(nextPos);
                    ++currentSegment;
                }
                update();
            } else {

                // 停止计时
                moveTimer->stop();
                moveTimer->deleteLater();
                moveTimer = nullptr;
                setAllButtonsEnabled(true); // 启用按钮
                isMoving = 0; // 设置移动状态
                update();
            }
            break;

        case 1:
            if (currentSegment < totalSegments) {
                QPointF currentPos = driver1.getPosition();
                QPointF nextPos = drivePath[currentSegment + 1];
                double distance = std::hypot(nextPos.x() - currentPos.x(), nextPos.y() - currentPos.y());

                if (distance > speed) {
                    double ratio = speed / distance;
                    QPointF moveStep((nextPos.x() - currentPos.x()) * ratio, (nextPos.y() - currentPos.y()) * ratio);
                    driver1.setPosition(currentPos + moveStep);
                } else {
                    driver1.setPosition(nextPos);
                    ++currentSegment;
                }
                update();
            } else {
                // 停止计时
                moveTimer->stop();
                moveTimer->deleteLater();
                moveTimer = nullptr;
                setAllButtonsEnabled(true); // 启用按钮
                isMoving = 0; // 设置移动状态
                update();
            }
            break;

        case 2:
            if (currentSegment < totalSegments) {
                QPointF currentPos = driver2.getPosition();
                QPointF nextPos = drivePath[currentSegment + 1];
                double distance = std::hypot(nextPos.x() - currentPos.x(), nextPos.y() - currentPos.y());

                if (distance > speed) {
                    double ratio = speed / distance;
                    QPointF moveStep((nextPos.x() - currentPos.x()) * ratio, (nextPos.y() - currentPos.y()) * ratio);
                    driver2.setPosition(currentPos + moveStep);
                } else {
                    driver2.setPosition(nextPos);
                    ++currentSegment;
                }
                update();
            } else {
                // 停止计时
                moveTimer->stop();
                moveTimer->deleteLater();
                moveTimer = nullptr;
                setAllButtonsEnabled(true); // 启用按钮
                isMoving = 0; // 设置移动状态
                update();
            }
            break;
        }
    } else {
        switch (currDriver) {
        case 0:
            if (currentSegment < totalSegments) {
                passenger.setIsVisible(false);
                QPointF currentPos = driver.getPosition();
                QPointF nextPos = path[currentSegment + 1];
                double distance = std::hypot(nextPos.x() - currentPos.x(), nextPos.y() - currentPos.y());

                if (distance > speed) {
                    double ratio = speed / distance;
                    QPointF moveStep((nextPos.x() - currentPos.x()) * ratio, (nextPos.y() - currentPos.y()) * ratio);
                    driver.setPosition(currentPos + moveStep);
                } else {
                    driver.setPosition(nextPos);
                    ++currentSegment;
                }
                update();
            } else {
                passenger.setPosition(driver.getPosition());
                passenger.setIsVisible(true);
                // 停止计时
                moveTimer->stop();
                moveTimer->deleteLater();
                moveTimer = nullptr;
                setAllButtonsEnabled(true); // 启用按钮
                isMoving = 0; // 设置移动状态
                update();
            }
            break;

        case 1:
            if (currentSegment < totalSegments) {
                passenger.setIsVisible(false);
                QPointF currentPos = driver1.getPosition();
                QPointF nextPos = path[currentSegment + 1];
                double distance = std::hypot(nextPos.x() - currentPos.x(), nextPos.y() - currentPos.y());

                if (distance > speed) {
                    double ratio = speed / distance;
                    QPointF moveStep((nextPos.x() - currentPos.x()) * ratio, (nextPos.y() - currentPos.y()) * ratio);
                    driver1.setPosition(currentPos + moveStep);
                } else {
                    driver1.setPosition(nextPos);
                    ++currentSegment;
                }
                update();
            } else {
                passenger.setPosition(driver1.getPosition());
                passenger.setIsVisible(true);
                // 停止计时
                moveTimer->stop();
                moveTimer->deleteLater();
                moveTimer = nullptr;
                setAllButtonsEnabled(true); // 启用按钮
                isMoving = 0; // 设置移动状态
                update();
            }
            break;

        case 2:
            if (currentSegment < totalSegments) {
                passenger.setIsVisible(false);
                QPointF currentPos = driver2.getPosition();
                QPointF nextPos = path[currentSegment + 1];
                double distance = std::hypot(nextPos.x() - currentPos.x(), nextPos.y() - currentPos.y());

                if (distance > speed) {
                    double ratio = speed / distance;
                    QPointF moveStep((nextPos.x() - currentPos.x()) * ratio, (nextPos.y() - currentPos.y()) * ratio);
                    driver2.setPosition(currentPos + moveStep);
                } else {
                    driver2.setPosition(nextPos);
                    ++currentSegment;
                }
                update();
            } else {
                passenger.setPosition(driver2.getPosition());
                passenger.setIsVisible(true);
                // 停止计时
                moveTimer->stop();
                moveTimer->deleteLater();
                moveTimer = nullptr;
                setAllButtonsEnabled(true); // 启用按钮
                isMoving = 0; // 设置移动状态
                update();
            }
            break;
        }
    }
}

// 查询距离最近的节点，找到对应的graph中的节点坐标
int MapWidget::findClosestNode(Passenger p) {
    QPointF passengerPos = p.getPosition();
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

// 找到最近的司机
int MapWidget::findNearestDriver() {
    QPointF passengerPosition = passenger.getPosition();
    std::vector<Passenger> drivers = {this->driver1, this->driver2, this->driver};

    Passenger nearestDriver;
    double minDistance = std::numeric_limits<double>::max();

    for (const auto &driver : drivers) {
        double distance = std::hypot(driver.getPosition().x() - passengerPosition.x(), driver.getPosition().y() - passengerPosition.y());
        if (distance < minDistance) {
            minDistance = distance;
            nearestDriver = driver;
        }
    }

    return nearestDriver.getState();
}

void MapWidget::setAllButtonsEnabled(bool isEnable) {
    CSU_Button->setEnabled(isEnable);
    CSU_OLD_Button->setEnabled(isEnable);
    CSUST_Button->setEnabled(isEnable);
    CSUFT_Button->setEnabled(isEnable);
    HNU_Button->setEnabled(isEnable);
    HNNU_Button->setEnabled(isEnable);
    HUIWANG_Button->setEnabled(isEnable);
    XIANGBIWO_Button->setEnabled(isEnable);
    XIANGYA_Button->setEnabled(isEnable);
    MEIXIHU_Button->setEnabled(isEnable);
    YANGHU_Button->setEnabled(isEnable);
    WUYI_Button->setEnabled(isEnable);
    NANJIAO_Button->setEnabled(isEnable);
    BISHAHU_Button->setEnabled(isEnable);
}

QPointF MapWidget::getRandomLocation() {
    srand(time(nullptr)); // 设置随机数种子
    int randomIndex = rand() % graph.getMaxNode();
    return graph.getLocCor(randomIndex);
}
