#include "graph.h"
#include "algorithms.h"
#include <cstdio>

using namespace graph;

void printTestResult(const char *testName, bool passed)
{
    printf("%-40s [%s]\n", testName, passed ? "PASSED" : "FAILED");
}

void testGraphConstructor()
{
    Graph g(5);
    bool passed = (g.getNumVertices() == 5);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            passed = passed && !g.hasEdge(i, j);
        }
    }

    printTestResult("Graph Constructor Test", passed);
}

void testAddEdge()
{
    Graph g(4);
    g.addEdge(0, 1, 5);
    g.addEdge(1, 2);
    g.addEdge(2, 3, 3);

    bool passed = g.hasEdge(0, 1) && g.hasEdge(1, 0);
    passed = passed && (g.getWeight(0, 1) == 5);
    passed = passed && g.hasEdge(1, 2) && (g.getWeight(1, 2) == 1);
    passed = passed && g.hasEdge(2, 3) && (g.getWeight(2, 3) == 3);

    g.addEdge(3, 4, 2);
    passed = passed && !g.hasEdge(3, 4);

    printTestResult("Add Edge Test", passed);
}

void testRemoveEdge()
{
    Graph g(3);
    g.addEdge(0, 1, 2);
    g.addEdge(1, 2, 3);

    g.removeEdge(0, 1);
    bool passed = !g.hasEdge(0, 1) && !g.hasEdge(1, 0);

    passed = passed && g.hasEdge(1, 2) && g.hasEdge(2, 1);

    g.removeEdge(0, 2);
    passed = passed && !g.hasEdge(0, 2);

    g.removeEdge(1, 3);
    passed = passed && g.hasEdge(1, 2);

    printTestResult("Remove Edge Test", passed);
}

void testHasEdge()
{
    Graph g(4);
    g.addEdge(0, 1);
    g.addEdge(2, 3);

    bool passed = g.hasEdge(0, 1) && g.hasEdge(1, 0);
    passed = passed && g.hasEdge(2, 3) && g.hasEdge(3, 2);
    passed = passed && !g.hasEdge(0, 2) && !g.hasEdge(1, 3);

    passed = passed && !g.hasEdge(0, 4) && !g.hasEdge(4, 0);

    printTestResult("Has Edge Test", passed);
}

void testGetWeight()
{
    Graph g(3);
    g.addEdge(0, 1, 5);
    g.addEdge(1, 2);

    bool passed = (g.getWeight(0, 1) == 5) && (g.getWeight(1, 0) == 5);
    passed = passed && (g.getWeight(1, 2) == 1) && (g.getWeight(2, 1) == 1);
    passed = passed && (g.getWeight(0, 2) == 0);

    passed = passed && (g.getWeight(0, 3) == 0) && (g.getWeight(3, 0) == 0);

    printTestResult("Get Weight Test", passed);
}

void testBFSAlgorithm()
{
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    Algorithms algo;
    Graph bfsTree = algo.bfs(g, 0);

    bool passed = bfsTree.hasEdge(0, 1) && bfsTree.hasEdge(0, 2);

    bool connectsTo3 = (bfsTree.hasEdge(1, 3) && !bfsTree.hasEdge(2, 3)) ||
                       (!bfsTree.hasEdge(1, 3) && bfsTree.hasEdge(2, 3));
    passed = passed && connectsTo3;

    passed = passed && bfsTree.hasEdge(2, 4);

    bool connectsTo5 = (bfsTree.hasEdge(3, 5) && !bfsTree.hasEdge(4, 5)) ||
                       (!bfsTree.hasEdge(3, 5) && bfsTree.hasEdge(4, 5));
    passed = passed && connectsTo5;

    printTestResult("BFS Algorithm Test", passed);
}

void testDFSAlgorithm()
{
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    Algorithms algo;
    Graph dfsTree = algo.dfs(g, 0);

    bool passed = true;

    int edgeCount = 0;
    for (int i = 0; i < 6; i++)
    {
        for (int j = i + 1; j < 6; j++)
        {
            if (dfsTree.hasEdge(i, j))
                edgeCount++;
        }
    }
    passed = passed && (edgeCount == 5);

    for (int i = 1; i < 6; i++)
    {
        bool connected = false;
        for (int j = 0; j < 6; j++)
        {
            if (dfsTree.hasEdge(i, j))
                connected = true;
        }
        passed = passed && connected;
    }

    printTestResult("DFS Algorithm Test", passed);
}

void testDijkstraAlgorithm()
{
    Graph g(5);
    g.addEdge(0, 1, 10);
    g.addEdge(0, 2, 5);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 1);
    g.addEdge(2, 1, 3);
    g.addEdge(2, 3, 9);
    g.addEdge(2, 4, 2);
    g.addEdge(3, 4, 4);
    g.addEdge(4, 3, 6);

    Algorithms algo;
    Graph shortestPathTree = algo.dijkstra(g, 0);

    bool passed = shortestPathTree.hasEdge(0, 2);
    passed = passed && shortestPathTree.hasEdge(2, 1) && !shortestPathTree.hasEdge(0, 1);
    passed = passed && shortestPathTree.hasEdge(1, 3);
    passed = passed && shortestPathTree.hasEdge(2, 4);

    printTestResult("Dijkstra Algorithm Test", passed);
}

void testPrimAlgorithm()
{
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    Algorithms algo;
    Graph mst = algo.prim(g, 0);

    bool passed = mst.hasEdge(0, 1) && mst.hasEdge(1, 2) &&
                  mst.hasEdge(1, 4) && mst.hasEdge(0, 3);

    int edgeCount = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            if (mst.hasEdge(i, j))
                edgeCount++;
        }
    }
    passed = passed && (edgeCount == 4);

    printTestResult("Prim Algorithm Test", passed);
}

void testKruskalAlgorithm()
{
    Graph g(5);
    g.addEdge(0, 1, 2);
    g.addEdge(0, 3, 6);
    g.addEdge(1, 2, 3);
    g.addEdge(1, 3, 8);
    g.addEdge(1, 4, 5);
    g.addEdge(2, 4, 7);
    g.addEdge(3, 4, 9);

    Algorithms algo;
    Graph mst = algo.kruskal(g);

    bool passed = mst.hasEdge(0, 1) && mst.hasEdge(1, 2) &&
                  mst.hasEdge(1, 4) && mst.hasEdge(0, 3);

    int edgeCount = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            if (mst.hasEdge(i, j))
                edgeCount++;
        }
    }
    passed = passed && (edgeCount == 4);

    printTestResult("Kruskal Algorithm Test", passed);
}

int main()
{
    printf("Running unit tests for Graph Algorithms project\n");
    printf("==============================================\n\n");

    printf("Graph Class Tests:\n");
    printf("-----------------\n");
    testGraphConstructor();
    testAddEdge();
    testRemoveEdge();
    testHasEdge();
    testGetWeight();
    printf("\n");

    printf("Algorithms Tests:\n");
    printf("----------------\n");
    testBFSAlgorithm();
    testDFSAlgorithm();
    testDijkstraAlgorithm();
    testPrimAlgorithm();
    testKruskalAlgorithm();
    printf("\n");

    printf("All tests completed.\n");

    return 0;
}