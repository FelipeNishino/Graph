#ifndef GRAPH_PRIORITYQUEUE_H
#define GRAPH_PRIORITYQUEUE_H

#include <vector>

class PriorityQueue {
    public:
        int* A;
        int n;
        PriorityQueue(int n);
    private:
        void swap(int &a, int &b);
        void climb(int i);
        void insert(int val);
        void descent(int i);
        int parent(int i);
        int left(int i);
        int right(int i);
};

#endif //GRAPH_PRIORITYQUEUE_H