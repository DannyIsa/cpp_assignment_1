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
        Graph(int vertices);

        ~Graph();

        void addEdge(int source, int destination, int weight = 1);

        void removeEdge(int source, int destination);

        void print_graph();

        bool hasEdge(int source, int destination);
        int getWeight(int source, int destination);
        int getNumVertices();
    };

}

#endif