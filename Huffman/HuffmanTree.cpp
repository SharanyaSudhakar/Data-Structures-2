#ifndef HUFFMANTREE_CPP
#define HUFFMANTREE_CPP

#include "HuffmanTree.h"
#include <iostream>
#include <ctype.h>

template<typename Data, typename Priority>
void HuffmanTree<Data, Priority>::makeTree(Heap<Data, Priority> & heapTree)
{
    while (heapTree.size() != 2)
    {
        Node<Data, Priority> *left(new Node<Data, Priority>()),
            *right(new Node<Data, Priority>());
        *left = heapTree.pop();
        *right = heapTree.pop();
        Priority newP = left->priority() + right->priority();
        Node<Data, Priority> newnode(newP, left, right);
        heapTree.push(newnode);
    }
    *root = heapTree.pop();
}

template<typename Data, typename Priority>
void HuffmanTree<Data, Priority>::makeTree()
{
    if (!root)
    {
        Node<Data, Priority> *newnode(new Node<Data, Priority>());
        root = newnode;
    }
    Node<Data, Priority> *current;
    std::cerr << "\nTREE from pattern table\n\n";
    for (auto& item : freqTable)
    {
        current = root;
        std::cerr << item.first << ": " << item.second << "    ";
        for (unsigned int i = 0; i < item.second.size(); i++)
        {
            Node<Data, Priority> *newnode(new Node<Data, Priority>());
            if (item.second[i] == '0')
            {
                if (!current->left())
                    current->setLeft(newnode);
                current = current->left();
            }
            else
            {
                if (!current->right())
                    current->setRight(newnode);
                current = current->right();
            }//end else
        }//end for
        current->setData(item.first);
    }
}

template<typename Data, typename Priority>
void HuffmanTree<Data, Priority>::encodeHelper(Node<Data, Priority>* root, std::string path)
{
    if (!root)
        return;

    encodeHelper(root->left(), path + '0');
    Data d = root->data();
    if (d)
        freqTable[d] = path;
    encodeHelper(root->right(), path + '1');
}


template<typename Data, typename Priority>
void HuffmanTree<Data, Priority>::dump()
{
    dumpHelper(root, 0);
}

template<typename Data, typename Priority>
void HuffmanTree<Data, Priority>::dumpHelper(Node<Data, Priority>* root, int indent)
{
    if (!root)
        return;
    indent++;
    dumpHelper(root->right(), indent);
    for (int i = 0; i < indent; i++)
        std::cerr << "    ";
    if (root->left() && root->right())
        std::cerr << root->priority() << std::endl;
    else
    {
        if (isprint(root->data()))
            std::cerr << root->data();
        else
            std::cerr << " \\n";
        if (root->priority())
            std::cerr << ": " << root->priority() << std::endl;
        else
            std::cerr << std::endl;
    }
    dumpHelper(root->left(), indent);
}
#endif // !HUFFMANTREE_CPP