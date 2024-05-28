#include "graph.h"

void Graph::addNode(int id, float x, float y, const std::string& name, const std::string& type) {
    nodes.push_back({id, x, y, name, type});
}

void Graph::addEdge(int from, int to, float weight, const std::string& type) {
    edges.push_back({from, to, weight, type});
}

const std::vector<Node>& Graph::getNodes() const {
    return nodes;
}

const std::vector<Edge>& Graph::getEdges() const {
    return edges;
}
