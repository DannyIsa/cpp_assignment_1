// daniisakov@gmail.com
#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "graph.h"
#include "data_structures.h"

namespace graph
{

    class Algorithms
    {
    private:
        void constructGraphFromParent(int *parent, int root, int n, Graph &result);

    public:
        Graph bfs(Graph &graph, int source);

        Graph dfs(Graph &graph, int source);

        Graph dijkstra(Graph &graph, int source);

        Graph prim(Graph &graph, int source);

        Graph kruskal(Graph &graph);
    };

}

#endif