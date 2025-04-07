// daniisakov@gmail.com
#ifndef GRAPH_H
#define GRAPH_H

namespace graph
{

    class Graph
    {
    private:
        int numVertices;
        int **adjacencyMatrix;

    public:
        // Constructor initializes a graph with fixed number of vertices
        Graph(int vertices);

        // Destructor to free allocated memory
        ~Graph();

        // Add an edge with optional weight (default is 1)
        void addEdge(int source, int destination, int weight = 1);

        // Remove an edge between two vertices
        void removeEdge(int source, int destination);

        // Print the graph representation
        void print_graph();

        // Helper methods
        bool hasEdge(int source, int destination);
        int getWeight(int source, int destination);
        int getNumVertices();
    };

} // end of namespace graph

#endif // GRAPH_H