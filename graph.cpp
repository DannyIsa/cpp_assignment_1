// daniisakov@gmail.com
#include "graph.h"
#include <cstdio> // For printf in print_graph

namespace graph
{

    Graph::Graph(int vertices)
    {
        numVertices = vertices;

        // Allocate memory for adjacency matrix
        adjacencyMatrix = new int *[numVertices];
        for (int i = 0; i < numVertices; i++)
        {
            adjacencyMatrix[i] = new int[numVertices];

            // Initialize all edges to 0 (no connections)
            for (int j = 0; j < numVertices; j++)
            {
                adjacencyMatrix[i][j] = 0;
            }
        }
    }

    Graph::~Graph()
    {
        // Free allocated memory
        for (int i = 0; i < numVertices; i++)
        {
            delete[] adjacencyMatrix[i];
        }
        delete[] adjacencyMatrix;
    }

    void Graph::addEdge(int source, int destination, int weight)
    {
        // Check if vertices are valid
        if (source >= 0 && source < numVertices &&
            destination >= 0 && destination < numVertices)
        {

            // For an undirected graph, add edges in both directions
            adjacencyMatrix[source][destination] = weight;
            adjacencyMatrix[destination][source] = weight;
        }
    }

    void Graph::removeEdge(int source, int destination)
    {
        // Check if vertices are valid
        if (source >= 0 && source < numVertices &&
            destination >= 0 && destination < numVertices)
        {

            // For an undirected graph, remove edges in both directions
            adjacencyMatrix[source][destination] = 0;
            adjacencyMatrix[destination][source] = 0;
        }
    }

    void Graph::print_graph()
    {
        printf("Graph Adjacency Matrix:\n");
        for (int i = 0; i < numVertices; i++)
        {
            for (int j = 0; j < numVertices; j++)
            {
                printf("%d ", adjacencyMatrix[i][j]);
            }
            printf("\n");
        }
    }

    bool Graph::hasEdge(int source, int destination)
    {
        if (source >= 0 && source < numVertices &&
            destination >= 0 && destination < numVertices)
        {
            return adjacencyMatrix[source][destination] != 0;
        }
        return false;
    }

    int Graph::getWeight(int source, int destination)
    {
        if (source >= 0 && source < numVertices &&
            destination >= 0 && destination < numVertices)
        {
            return adjacencyMatrix[source][destination];
        }
        return 0;
    }

    int Graph::getNumVertices()
    {
        return numVertices;
    }

}