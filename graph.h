#ifndef GRAPH_H
#define GRAPH_H

#define MAP_X 0
#define MAP_Y 0

// 中南大学新校区
#define CSU_X 552
#define CSU_Y 479
// 中南大学校本部
#define CSU_OLD_X 428
#define CSU_OLD_Y 353
// 回望书店
#define HUIWANG_X 599
#define HUIWANG_Y 361
// 湖南大学
#define HNU_X 650
#define HNU_Y 130
// 梅溪湖
#define MEIXIHU_X 374
#define MEIXIHU_Y 34
// 象鼻窝
#define XIANGBIWO_X 83
#define XIANGBIWO_Y 271
// 湖南师范大学
#define HNNU_X 171
#define HNNU_Y 615
// 碧沙湖
#define BISHAHU_X 807
#define BISHAHU_Y 394
// 长沙理工大学
#define CSUST_X 902
#define CSUST_Y 436
// 洋湖
#define YANGHU_X 502
#define YANGHU_Y 603
// 中南林业科技大学
#define CSUFT_X 1014
#define CSUFT_Y 641
// 五一广场
#define WUYI_X 906
#define WUYI_Y 152
// 湘雅二医院
#define XIANGYA_X 984
#define XIANGYA_Y 157
// 南郊公园
#define NANJIAO_X 905
#define NANJIAO_Y 565


#include <QPointF>

class Graph {
private:
    static const int MAX_NODES = 14;
    static const int MAX_EDGES = 55;  // 估计的边的最大数量

    QPointF nodeList[MAX_NODES];
    int adjacencyMatrix[MAX_NODES][MAX_NODES];
    int numNodes;
    int numEdges;

public:
    Graph();  // 构造函数

    void addNode(const QPointF& node);
    void addEdge(const QPointF& source, const QPointF& target, int weight);
    std::vector<QPointF> dijkstra(const QPointF& source, const QPointF& target);

    QPointF getLoc(int index);
    QPointF getLocCor(int location);
    int getMaxNode();
    int getWeight(int s_index, int t_index);
};

#endif // GRAPH_H
