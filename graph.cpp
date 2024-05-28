#include "graph.h"
#include <limits>
#include <queue>
#include <algorithm>

Graph::Graph() {
    numNodes = 0;
    numEdges = 0;
    // 初始化邻接矩阵
    for (int i = 0; i < MAX_NODES; ++i) {
        for (int j = 0; j < MAX_NODES; ++j) {
            adjacencyMatrix[i][j] = std::numeric_limits<int>::max();  // 初始化为最大值表示无连接
        }
    }
}

void Graph::addNode(const QPointF& node) {
    if (numNodes < MAX_NODES) {
        nodeList[numNodes++] = node;
    }
}

void Graph::addEdge(const QPointF& source, const QPointF& target, int weight) {
    int sourceIndex = -1;
    int targetIndex = -1;

    // 查找源节点和目标节点的索引
    for (int i = 0; i < numNodes; ++i) {
        if (nodeList[i] == source) {
            sourceIndex = i;
        }
        if (nodeList[i] == target) {
            targetIndex = i;
        }
    }

    // 如果找到了源节点和目标节点，则添加边
    if (sourceIndex != -1 && targetIndex != -1) {
        adjacencyMatrix[sourceIndex][targetIndex] = weight;
        adjacencyMatrix[targetIndex][sourceIndex] = weight;  // 如果是无向图，同时添加反向边
        ++numEdges;
    }
}

QPointF Graph::getLocCor(int location)
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
