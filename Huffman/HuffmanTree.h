#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H
#include "Heap.cpp"
#include "Node.h"
#include <string>
#include <map>
#include <utility>

template<typename Data, typename Priority>
class HuffmanTree
{
public:
    HuffmanTree() : root(new Node<Data, Priority>()) {};
    void makeTree(Heap<Data, Priority> &heapTree);
    void makeTree();
    void dump();
    std::string lookup(Data d) { return freqTable[d]; };
    void addPattern(Data& d, std::string& str) {
        freqTable[d] = str;
    };
    std::map<Data, std::string> getFreqTable() {
        encodeHelper(root, "");
        return freqTable;
    };

    Node<Data, Priority>* getRoot() { return root; };
    std::string getPattern(Data d) { return freqTable[d]; };

private:
    Node<Data, Priority>* root;
    std::map<Data, std::string> freqTable;
    void dumpHelper(Node<Data, Priority>* root, int indent);
    void encodeHelper(Node<Data, Priority>* root, std::string path);
};
#endif // !HUFFMANTREE_H
