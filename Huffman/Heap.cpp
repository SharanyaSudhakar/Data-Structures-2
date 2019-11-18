#ifndef HEAP_CPP
#define HEAP_CPP

#include "Heap.h"
#include <iostream>

template<typename Data, typename Priority>
void Heap<Data, Priority>::push(const Node<Data, Priority>& node)
{
    dataArr.push_back(node);
    mSize++;
    int current = size() - 1;
    int parent = getParent(current);
    while (parent != 0)
    {
        parent = getParent(current);
        if (dataArr[current] < dataArr[parent])
        {
            nodeSwap(current, parent);
            current = parent;
        }
        else
            break;
    }
}

template <typename Data, typename Priority>
 void Heap<Data, Priority>::push(Data data, Priority priority)
 {
     push(Node<Data, Priority>(data, priority));
 }

 template <typename Data, typename Priority>
 void Heap<Data, Priority>::dump() const
 {
     for (auto& item : dataArr)
     {
         if ((int)item.data() != 10)
             std::cerr << item.data();
         else
             std::cerr << " \\n";
         std::cerr << ": " << item.priority() << "    ";
     }
     std::cerr << std::endl;
 }

template<typename Data, typename Priority>
Node<Data, Priority> Heap<Data, Priority>::pop()
 {
     Node<Data, Priority> node(dataArr[1]);
     nodeSwap(1,--mSize);
     dataArr.pop_back();

     int current = 1;
     int left = 2 * current;
     int right = left + 1;

     while (true)
     {
         left = 2 * current;
         right = left + 1;
         if (current < size() && left < size() && right < size())
         {
             int min = (dataArr[left] < dataArr[right]) ? left : right;
             if (dataArr[min] < dataArr[current])
             {
                 nodeSwap(min, current);
                 current = min;
             }
             else
                 break;
         }
         else
             break;
     }
     return node;
 }
#endif // !HEAP_CPP