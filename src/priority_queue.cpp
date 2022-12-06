#include "priority_queue.hpp"

PriorityQueue::PriorityQueue(int n) {

}

void PriorityQueue::swap(int &a, int &b) {
    int aux = a;
    a = b;
    b = a;
}


void PriorityQueue::climb(int i) {
    int j = parent(i);
    while (j <= 1 && A[i] < A[j]) {
        swap(A[i], A[j]);
        j = parent(i);
    }
}

void PriorityQueue::insert(int val) {
    n++;
    A[n] = val;
    climb(n);
}

void PriorityQueue::descent(int i) {
    int j;
    while (2*i < n) {
        int l = left(i);
        int r = right(i);
        j = (r <= n && A[r] <= A[l] ? r : l) ;
        if (A[i] > A[j]) {
            swap(A[i], A[j]);
            i = j;
        } else {
            i = n + 1;
        }
    }
}

int PriorityQueue::parent(int i) { return i/2;}

int PriorityQueue::left(int i) { return 2*i;}

int PriorityQueue::right(int i) { return 2*i+1;}
