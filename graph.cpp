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

    for (int i = 0; i < MAX_NODES; i++) {
        addNode(getLocCor(i));
    }


    addEdge(getLocCor(0), getLocCor(1), 228);
    addEdge(getLocCor(0), getLocCor(2), 162);
    addEdge(getLocCor(0), getLocCor(7), 188);
    addEdge(getLocCor(1), getLocCor(7), 347);
    addEdge(getLocCor(1), getLocCor(4), 327);
    addEdge(getLocCor(2), getLocCor(3), 298);
    addEdge(getLocCor(3), getLocCor(4), 370);
    addEdge(getLocCor(4), getLocCor(5), 1);
    addEdge(getLocCor(5), getLocCor(6), 1);
    addEdge(getLocCor(6), getLocCor(7), 1);
    addEdge(getLocCor(7), getLocCor(8), 1);
    addEdge(getLocCor(2), getLocCor(10), 1);
    addEdge(getLocCor(3), getLocCor(11), 1);
    addEdge(getLocCor(9), getLocCor(10), 1);
    addEdge(getLocCor(11), getLocCor(13), 1);
    addEdge(getLocCor(9), getLocCor(11), 1);
    addEdge(getLocCor(8), getLocCor(9), 1);
    addEdge(getLocCor(8), getLocCor(12), 1);
    addEdge(getLocCor(12), getLocCor(13), 1);

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
        adjacencyMatrix[targetIndex][sourceIndex] = weight;  // 无向图，同时添加反向边
        ++numEdges;
    }
}

QPointF Graph::getLocCor(int location) {
    int x, y;
    switch (location)
    {
    case 0: //中南大学新校区
        x = CSU_X - MAP_X;
        y = CSU_Y - MAP_Y;
        break;
    case 1: //中南大学校本部
        x = CSU_OLD_X - MAP_X;
        y = CSU_OLD_Y - MAP_Y;
        break;
    case 2: //回望书店
        x = HUIWANG_X -MAP_X;
        y = HUIWANG_Y -MAP_Y;
        break;
    case 3: //湖南大学
        x = HNU_X - MAP_X;
        y = HNU_Y - MAP_Y;
        break;
    case 4: //梅溪湖
        x = MEIXIHU_X - MAP_X;
        y = MEIXIHU_Y - MAP_Y;
        break;
    case 5: // 象鼻窝森林公园
        x = XIANGBIWO_X - MAP_X;
        y = XIANGBIWO_Y - MAP_Y;
        break;
    case 6: // 湖南师范大学
        x = HNNU_X - MAP_X;
        y = HNNU_Y - MAP_Y;
        break;
    case 7: // 洋湖湿地公园
        x = YANGHU_X - MAP_X;
        y = YANGHU_Y - MAP_Y;
        break;
    case 8: // 南郊公园
        x = NANJIAO_X - MAP_X;
        y = NANJIAO_Y - MAP_Y;
        break;
    case 9: // 长沙理工大学
        x = CSUST_X - MAP_X;
        y = CSUST_Y - MAP_Y;
        break;
    case 10: // 碧沙湖
        x = BISHAHU_X - MAP_X;
        y = BISHAHU_Y - MAP_Y;
        break;
    case 11: // 五一广场
        x = WUYI_X - MAP_X;
        y = WUYI_Y - MAP_Y;
        break;
    case 12: // 中南林业科技大学
        x = CSUFT_X - MAP_X;
        y = CSUFT_Y - MAP_Y;
        break;
    case 13: // 湘雅二医院
        x = XIANGYA_X - MAP_X;
        y = XIANGYA_Y - MAP_Y;
        break;
    }

    return QPointF(x, y);
}

std::vector<QPointF> Graph::dijkstra(const QPointF& source, const QPointF& target) {
    std::vector<int> distance(numNodes, std::numeric_limits<int>::max());
    std::vector<int> parent(numNodes, -1);
    std::vector<bool> visited(numNodes, false);

    auto compare = [&](int left, int right) {
        return distance[left] > distance[right];
    };
    std::priority_queue<int, std::vector<int>, decltype(compare)> pq(compare);

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

    // 如果找不到源节点或目标节点，返回空路径
    if (sourceIndex == -1 || targetIndex == -1) {
        return {};
    }

    distance[sourceIndex] = 0;
    pq.push(sourceIndex);

    // Dijkstra算法
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();

        if (visited[u]) {
            continue;
        }

        visited[u] = true;

        for (int v = 0; v < numNodes; ++v) {
            if (adjacencyMatrix[u][v] != std::numeric_limits<int>::max() && !visited[v]) {
                int weight = adjacencyMatrix[u][v];
                if (distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                    parent[v] = u;
                    pq.push(v);
                }
            }
        }
    }

    // 构建最短路径
    std::vector<QPointF> shortestPath;
    for (int v = targetIndex; v != -1; v = parent[v]) {
        shortestPath.push_back(nodeList[v]);
    }
    std::reverse(shortestPath.begin(), shortestPath.end());

    return shortestPath;
}

int Graph::getMaxNode() {
    return MAX_NODES;
}

int Graph::getWeight(int s_index, int t_index) {
    return adjacencyMatrix[s_index][t_index];
}

QPointF Graph::getLoc(int index) {
    return nodeList[index];
}
