// daniisakov@gmail.com
#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

namespace data_structures
{

    class Queue
    {
    private:
        int *data;
        int capacity;
        int front;
        int rear;
        int count;

    public:
        Queue(int size);
        ~Queue();
        void enqueue(int value);
        int dequeue();
        bool isEmpty();
        bool isFull();
        int size();
    };

    class Stack
    {
    private:
        int *data;
        int capacity;
        int top;

    public:
        Stack(int size);
        ~Stack();
        void push(int value);
        int pop();
        int peek();
        bool isEmpty();
        bool isFull();
    };

    class PriorityQueue
    {
    private:
        struct Node
        {
            int vertex;
            int priority;
        };

        Node *heap;
        int capacity;
        int size;
        int *positions; // To track positions of vertices in the heap

        void heapify(int index);
        void swap(Node &a, Node &b);

    public:
        PriorityQueue(int capacity);
        ~PriorityQueue();
        void insert(int vertex, int priority);
        int extractMin();
        void decreaseKey(int vertex, int priority);
        bool isEmpty();
        bool contains(int vertex);
        int getPriority(int vertex);
    };

    class DisjointSet
    {
    private:
        int *parent;
        int *rank;
        int n;

    public:
        DisjointSet(int n);
        ~DisjointSet();
        int find(int x);
        void Union(int x, int y);
        bool sameSet(int x, int y);
    };

}

#endif