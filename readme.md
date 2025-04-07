<!-- daniisakov@gmail.com -->

# CPP - Assignment 1

### Data Structures

Custom implementations of essential data structures:

- **Queue**: Used for BFS algorithm
- **Stack**: Used for DFS algorithm (recursive implementation also available)
- **PriorityQueue**: Used for Dijkstra's and Prim's algorithms
- **DisjointSet**: Used for Kruskal's algorithm (Union-Find data structure)

### Graph Class

The Graph class represents the graph structure using an adjacency matrix.

Key methods:

- `addEdge(source, destination, weight)`: Adds an edge between two vertices with a specified weight
- `removeEdge(source, destination)`: Removes an edge between two vertices
- `print_graph()`: Displays the graph in a readable format
- `hasEdge(source, destination)`: Checks if an edge exists
- `getWeight(source, destination)`: Gets the weight of an edge
- `getNumVertices()`: Returns the number of vertices in the graph

### Algorithms Class

Implements various graph algorithms:

1. **BFS (Breadth-First Search)**
2. **DFS (Depth-First Search)**
3. **Dijkstra's Algorithm**
4. **Prim's Algorithm**
5. **Kruskal's Algorithm**

## Building and Running

### Build Instructions

```
make Main      # Compiles the program
make test      # Runs the test program
make valgrind  # Runs with valgrind to check for memory leaks
make clean     # Cleans all build files
```
