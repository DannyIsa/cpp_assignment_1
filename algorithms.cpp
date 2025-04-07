// daniisakov@gmail.com
#include "algorithms.h"
#include <cstdio> // For printf

namespace graph
{

    // Helper method to construct a graph from parent array
    void Algorithms::constructGraphFromParent(int *parent, int root, int n, Graph &result)
    {
        for (int i = 0; i < n; i++)
        {
            if (parent[i] != -1)
            {
                result.addEdge(parent[i], i, 1); // Default weight 1 for BFS/DFS
            }
        }
    }

    Graph Algorithms::bfs(Graph &graph, int source)
    {
        int n = graph.getNumVertices();
        Graph resultGraph(n);

        // Initialize visited array and parent array
        bool *visited = new bool[n];
        int *parent = new int[n];

        for (int i = 0; i < n; i++)
        {
            visited[i] = false;
            parent[i] = -1;
        }

        data_structures::Queue queue(n);
        visited[source] = true;
        queue.enqueue(source);

        while (!queue.isEmpty())
        {
            int u = queue.dequeue();

            for (int v = 0; v < n; v++)
            {
                if (graph.hasEdge(u, v) && !visited[v])
                {
                    visited[v] = true;
                    parent[v] = u;
                    queue.enqueue(v);
                }
            }
        }

        // Construct tree from parent array
        constructGraphFromParent(parent, source, n, resultGraph);

        // Clean up
        delete[] visited;
        delete[] parent;

        return resultGraph;
    }

    void dfsRecursive(Graph &graph, int vertex, bool *visited, int *parent, Graph &resultGraph)
    {
        visited[vertex] = true;

        for (int i = 0; i < graph.getNumVertices(); i++)
        {
            if (graph.hasEdge(vertex, i) && !visited[i])
            {
                parent[i] = vertex;
                resultGraph.addEdge(vertex, i, graph.getWeight(vertex, i));
                dfsRecursive(graph, i, visited, parent, resultGraph);
            }
        }
    }

    Graph Algorithms::dfs(Graph &graph, int source)
    {
        int n = graph.getNumVertices();
        Graph resultGraph(n);

        bool *visited = new bool[n];
        int *parent = new int[n];

        for (int i = 0; i < n; i++)
        {
            visited[i] = false;
            parent[i] = -1;
        }

        dfsRecursive(graph, source, visited, parent, resultGraph);

        // Clean up
        delete[] visited;
        delete[] parent;

        return resultGraph;
    }

    Graph Algorithms::dijkstra(Graph &graph, int source)
    {
        int n = graph.getNumVertices();
        Graph resultGraph(n);

        // Create a priority queue to store vertices and their distances
        data_structures::PriorityQueue pq(n);

        // Distance array and parent array
        int *dist = new int[n];
        int *parent = new int[n];

        // Initialize all distances as INFINITE and parent as -1
        for (int i = 0; i < n; i++)
        {
            dist[i] = 9999999; // A large value to represent infinity
            parent[i] = -1;
        }

        // Distance of source vertex from itself is always 0
        dist[source] = 0;

        // Add source vertex to the priority queue
        pq.insert(source, 0);

        // Loop until priority queue becomes empty
        while (!pq.isEmpty())
        {
            // Extract the vertex with minimum distance
            int u = pq.extractMin();

            // Traverse all adjacent vertices of u
            for (int v = 0; v < n; v++)
            {
                if (graph.hasEdge(u, v))
                {
                    int weight = graph.getWeight(u, v);

                    // If there is a shorter path to v through u
                    if (dist[v] > dist[u] + weight)
                    {
                        // Update distance of v
                        dist[v] = dist[u] + weight;
                        parent[v] = u;

                        // Update priority queue
                        if (pq.contains(v))
                        {
                            pq.decreaseKey(v, dist[v]);
                        }
                        else
                        {
                            pq.insert(v, dist[v]);
                        }
                    }
                }
            }
        }

        // Construct tree from parent array
        for (int i = 0; i < n; i++)
        {
            if (parent[i] != -1)
            {
                resultGraph.addEdge(parent[i], i, graph.getWeight(parent[i], i));
            }
        }

        // Clean up
        delete[] dist;
        delete[] parent;

        return resultGraph;
    }

    Graph Algorithms::prim(Graph &graph, int source)
    {
        int n = graph.getNumVertices();
        Graph resultGraph(n);

        // Create a priority queue to store vertices and their key values
        data_structures::PriorityQueue pq(n);

        // Key values used to pick minimum weight edge
        int *key = new int[n];

        // To store parent array which is used to construct MST
        int *parent = new int[n];

        // To keep track of vertices included in MST
        bool *inMST = new bool[n];

        // Initialize all keys as INFINITE and parent as -1
        for (int i = 0; i < n; i++)
        {
            key[i] = 9999999;
            parent[i] = -1;
            inMST[i] = false;
        }

        // Start with the source vertex
        key[source] = 0;
        pq.insert(source, 0);

        // While priority queue is not empty
        while (!pq.isEmpty())
        {
            // Extract the vertex with minimum key
            int u = pq.extractMin();
            inMST[u] = true;

            // Traverse all adjacent vertices of u
            for (int v = 0; v < n; v++)
            {
                // If v is not in MST and there is an edge from u to v
                if (graph.hasEdge(u, v) && !inMST[v])
                {
                    int weight = graph.getWeight(u, v);

                    // If weight of edge (u,v) is less than current key of v
                    if (weight < key[v])
                    {
                        // Update key value and parent of v
                        key[v] = weight;
                        parent[v] = u;

                        // Update priority queue
                        if (pq.contains(v))
                        {
                            pq.decreaseKey(v, key[v]);
                        }
                        else
                        {
                            pq.insert(v, key[v]);
                        }
                    }
                }
            }
        }

        // Construct MST from parent array
        for (int i = 0; i < n; i++)
        {
            if (parent[i] != -1)
            {
                resultGraph.addEdge(parent[i], i, graph.getWeight(parent[i], i));
            }
        }

        // Clean up
        delete[] key;
        delete[] parent;
        delete[] inMST;

        return resultGraph;
    }

    // Comparator for sorting edges
    struct Edge
    {
        int src, dest, weight;
    };

    Graph Algorithms::kruskal(Graph &graph)
    {
        int n = graph.getNumVertices();
        Graph resultGraph(n);

        // Create a vector to store all edges
        int edgeCount = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (graph.hasEdge(i, j))
                {
                    edgeCount++;
                }
            }
        }

        // Create an array of edges
        Edge *edges = new Edge[edgeCount];
        int e = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (graph.hasEdge(i, j))
                {
                    edges[e].src = i;
                    edges[e].dest = j;
                    edges[e].weight = graph.getWeight(i, j);
                    e++;
                }
            }
        }

        // Sort edges in non-decreasing order of their weight
        // Using a simple bubble sort (inefficient but doesn't use STL)
        for (int i = 0; i < edgeCount - 1; i++)
        {
            for (int j = 0; j < edgeCount - i - 1; j++)
            {
                if (edges[j].weight > edges[j + 1].weight)
                {
                    Edge temp = edges[j];
                    edges[j] = edges[j + 1];
                    edges[j + 1] = temp;
                }
            }
        }

        // Create disjoint sets
        data_structures::DisjointSet ds(n);

        // Process all sorted edges
        for (int i = 0; i < edgeCount; i++)
        {
            int u = edges[i].src;
            int v = edges[i].dest;

            // Check if adding this edge creates a cycle
            if (!ds.sameSet(u, v))
            {
                // Add this edge to MST
                resultGraph.addEdge(u, v, edges[i].weight);

                // Merge sets
                ds.Union(u, v);
            }
        }

        // Clean up
        delete[] edges;

        return resultGraph;
    }

}