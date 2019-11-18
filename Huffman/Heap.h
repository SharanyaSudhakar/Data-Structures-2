#ifndef Heap_H
#define Heap_H

#include <vector>
#include <utility>
#include "Node.h"
#include <iostream>

template <typename Data, typename Priority>
class Heap
{
public:
    Heap()
    {
        dataArr.push_back(Node<Data, Priority>(' ',-1));
        mSize = 1;
    };
    void push(Data data, Priority priority);
    void push(const Node<Data, Priority>& node);
    Node<Data, Priority> pop();
    bool isEmpty() const {return (size() == 1);}
    void dump() const;
    int size() const { return mSize; };

private:
    std::vector<Node<Data, Priority>> dataArr;
    int mSize;
    int getParent(int current){ return (current % 2 == 1) ? (current - 1) / 2 : current / 2; }
    void nodeSwap(int from, int to)
    {
        std::swap(dataArr[from],dataArr[to]);
    }
};
#endif