#include "graph.h"
#include "algorithms.h"
#include <cstdio>

using namespace graph;

int main()
{
    Graph g(6);

    g.addEdge(0, 1, 2);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 7);
    g.addEdge(2, 4, 3);
    g.addEdge(3, 4, 2);
    g.addEdge(3, 5, 1);
    g.addEdge(4, 5, 5);

    printf("Original Graph:\n");
    g.print_graph();

    Algorithms algo;

    printf("\nBFS Tree from vertex 0:\n");
    Graph bfs_tree = algo.bfs(g, 0);
    bfs_tree.print_graph();

    printf("\nDFS Tree from vertex 0:\n");
    Graph dfs_tree = algo.dfs(g, 0);
    dfs_tree.print_graph();

    printf("\nShortest Path Tree (Dijkstra) from vertex 0:\n");
    Graph sp_tree = algo.dijkstra(g, 0);
    sp_tree.print_graph();

    printf("\nMinimum Spanning Tree (Prim) from vertex 0:\n");
    Graph prim_tree = algo.prim(g, 0);
    prim_tree.print_graph();

    printf("\nMinimum Spanning Tree (Kruskal):\n");
    Graph kruskal_tree = algo.kruskal(g);
    kruskal_tree.print_graph();

    return 0;
}