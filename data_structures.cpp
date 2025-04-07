// daniisakov@gmail.com
#include "data_structures.h"

namespace data_structures
{

    Queue::Queue(int size)
    {
        capacity = size;
        data = new int[capacity];
        front = 0;
        rear = -1;
        count = 0;
    }

    Queue::~Queue()
    {
        delete[] data;
    }

    void Queue::enqueue(int value)
    {
        if (!isFull())
        {
            rear = (rear + 1) % capacity;
            data[rear] = value;
            count++;
        }
    }

    int Queue::dequeue()
    {
        int value = -1; // Default error value
        if (!isEmpty())
        {
            value = data[front];
            front = (front + 1) % capacity;
            count--;
        }
        return value;
    }

    bool Queue::isEmpty()
    {
        return (count == 0);
    }

    bool Queue::isFull()
    {
        return (count == capacity);
    }

    int Queue::size()
    {
        return count;
    }

    Stack::Stack(int size)
    {
        capacity = size;
        data = new int[capacity];
        top = -1;
    }

    Stack::~Stack()
    {
        delete[] data;
    }

    void Stack::push(int value)
    {
        if (!isFull())
        {
            data[++top] = value;
        }
    }

    int Stack::pop()
    {
        if (!isEmpty())
        {
            return data[top--];
        }
        return -1; // Error value for empty stack
    }

    int Stack::peek()
    {
        if (!isEmpty())
        {
            return data[top];
        }
        return -1; // Error value for empty stack
    }

    bool Stack::isEmpty()
    {
        return (top == -1);
    }

    bool Stack::isFull()
    {
        return (top == capacity - 1);
    }

    PriorityQueue::PriorityQueue(int maxCapacity)
    {
        capacity = maxCapacity;
        heap = new Node[capacity];
        positions = new int[capacity];
        size = 0;

        // Initialize positions array
        for (int i = 0; i < capacity; i++)
        {
            positions[i] = -1;
        }
    }

    PriorityQueue::~PriorityQueue()
    {
        delete[] heap;
        delete[] positions;
    }

    void PriorityQueue::swap(Node &a, Node &b)
    {
        Node temp = a;
        a = b;
        b = temp;

        // Update positions
        positions[a.vertex] = positions[b.vertex];
        positions[b.vertex] = positions[a.vertex];
    }

    void PriorityQueue::heapify(int idx)
    {
        int smallest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < size && heap[left].priority < heap[smallest].priority)
            smallest = left;

        if (right < size && heap[right].priority < heap[smallest].priority)
            smallest = right;

        if (smallest != idx)
        {
            positions[heap[idx].vertex] = smallest;
            positions[heap[smallest].vertex] = idx;

            // Swap nodes
            Node temp = heap[idx];
            heap[idx] = heap[smallest];
            heap[smallest] = temp;

            heapify(smallest);
        }
    }

    void PriorityQueue::insert(int vertex, int priority)
    {
        if (size == capacity)
            return;

        // Insert new node at the end
        int i = size;
        heap[i].vertex = vertex;
        heap[i].priority = priority;
        positions[vertex] = i;
        size++;

        // Fix the min heap property if violated
        while (i > 0 && heap[(i - 1) / 2].priority > heap[i].priority)
        {
            // Update positions
            positions[heap[i].vertex] = (i - 1) / 2;
            positions[heap[(i - 1) / 2].vertex] = i;

            // Swap with parent
            Node temp = heap[i];
            heap[i] = heap[(i - 1) / 2];
            heap[(i - 1) / 2] = temp;

            i = (i - 1) / 2;
        }
    }

    int PriorityQueue::extractMin()
    {
        if (isEmpty())
            return -1;

        // Store the root (minimum) node
        int root = heap[0].vertex;

        // Replace root with last node
        heap[0] = heap[size - 1];
        positions[heap[0].vertex] = 0;
        positions[root] = -1;
        size--;

        // Restore the heap property
        heapify(0);

        return root;
    }

    void PriorityQueue::decreaseKey(int vertex, int priority)
    {
        // Get the index of the vertex
        int i = positions[vertex];

        if (i == -1 || heap[i].priority <= priority)
            return;

        // Update the priority
        heap[i].priority = priority;

        // Fix the min heap property if violated
        while (i > 0 && heap[(i - 1) / 2].priority > heap[i].priority)
        {
            // Update positions
            positions[heap[i].vertex] = (i - 1) / 2;
            positions[heap[(i - 1) / 2].vertex] = i;

            // Swap with parent
            Node temp = heap[i];
            heap[i] = heap[(i - 1) / 2];
            heap[(i - 1) / 2] = temp;

            i = (i - 1) / 2;
        }
    }

    bool PriorityQueue::isEmpty()
    {
        return size == 0;
    }

    bool PriorityQueue::contains(int vertex)
    {
        return positions[vertex] != -1;
    }

    int PriorityQueue::getPriority(int vertex)
    {
        int i = positions[vertex];
        if (i != -1)
            return heap[i].priority;
        return -1; // Error value
    }

    DisjointSet::DisjointSet(int numElements)
    {
        n = numElements;
        parent = new int[n];
        rank = new int[n];

        // Initialize: each element is its own parent
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    DisjointSet::~DisjointSet()
    {
        delete[] parent;
        delete[] rank;
    }

    // Find with path compression
    int DisjointSet::find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    // Union by rank
    void DisjointSet::Union(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY)
            return;

        // Attach smaller rank tree under root of higher rank tree
        if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;
        else if (rank[rootX] > rank[rootY])
            parent[rootY] = rootX;
        else
        {
            // If ranks are same, make one as root and increment its rank
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }

    bool DisjointSet::sameSet(int x, int y)
    {
        return find(x) == find(y);
    }

}