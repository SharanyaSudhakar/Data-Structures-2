//-----------------------------------------------------
/*
Class file implementation referenced from class
Prof. Morris Bernstein
*/
//----------------------------------------------------

#include <iostream>
#include <utility>
#include "bst.h"

template<class Key, class Value>
inline Value & BST<Key, Value>::Node::findKey(Key key)
{
    if (key == mKey)
    return mVal;

    if (key < mKey)
        if (!mleftChild)
        {
            mleftChild = new Node(key);
            return mleftChild->mVal;
        }
        else
            return mleftChild->findKey(key);
    else
    if (!mrightChild)
    {
        mrightChild = new Node(key);
        return mrightChild->mVal;
    }
    else
    return mrightChild->findKey(key);
}

template<class Key, class Value>
BST<Key, Value>::Iterator::Iterator(Node* root) {
    if (!root) {
        mCurrent = nullptr;
        return;
    }
    leftmost(root);
    mCurrent = mStack.top();
    mStack.pop();
}

template<class Key, class Value>
typename BST<Key, Value>::Iterator& BST<Key, Value>::Iterator::operator++() {
    leftmost(mCurrent->rightChild());
    if (mStack.empty()) {
        mCurrent = nullptr;
        return *this;
    }
    mCurrent = mStack.top();
    mStack.pop();
    return *this;
}

template<class Key, class Value>
void BST<Key, Value>::Iterator::leftmost(typename BST<Key,Value>::Node* p) {
    while (p) {
        mStack.push(p);
        p = p->leftChild();
    }
}

template<class Key, class Value>
Value & BST<Key, Value>::operator[](const Key & key)
{
    if (!mRoot)
    {
        mRoot = new Node(key);
        return mRoot->value();
    }
    return mRoot->findKey(key);
}

//---------------------------------------------------------------------------
// displaySideways 
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.

//Source: Prof. Zander's Lab2 Assignment Question
//--------------------------------------------------------------------------

template<class Key, class Value>
void BST<Key, Value>::displaySideways() const {
    sideways(mRoot, 0);
}


template<class Key, class Value>
void BST<Key, Value>::sideways(Node* current, int level) const {
    if (current != NULL) {
        level++;
        sideways(current->rightChild(), level);

        // indent for readability, 4 spaces per depth level
        for (int i = level; i >= 0; i--) {
            std::cout << "    ";
        }

        std::cout << current->key() << std::endl;        // display information of object
        sideways(current->leftChild(), level);
    }
}