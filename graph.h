#ifndef GRAPH_H
#define GRAPH_H

#define MAP_X 0
#define MAP_Y 0

#define CSU_X 570
#define CSU_Y 516

#include <QPointF>

class Graph {
private:
    static const int MAX_NODES = 11;
    static const int MAX_EDGES = 55;  // 估计的边的最大数量

    QPointF nodeList[MAX_NODES];
    int adjacencyMatrix[MAX_NODES][MAX_NODES];
    int numNodes;
    int numEdges;

public:
    Graph();  // 构造函数

    void addNode(const QPointF& node);
    void addEdge(const QPointF& source, const QPointF& target, int weight);
    QPointF getLocCor(int location);
};

#endif // GRAPH_H
