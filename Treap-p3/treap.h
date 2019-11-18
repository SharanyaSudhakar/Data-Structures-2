//-----------------------------------------------------------
/*
This treap heder uses the resetPriority method to balance the 
tree at every insert. Balancing happens immediately after an 
insert and the node is bubbled up to position.
*/
//------------------------------------------------------------
#ifndef BST_H
#define BST_H

#include <string>
#include <iostream>
#include <stack>
#include <cstdlib>
#include <utility>

template<typename Key, typename Value>
class BST
{
    class Node;
public:
    BST() :mRoot(nullptr){};
    void setRoot(Node* node) { mRoot = node; };
    void displaySideways() const { sideways(mRoot, 0); };
    Value& operator[](const Key& key); 
    void print()const { printHelper(mRoot); };

    class Iterator {
    public:
        Iterator(Node* root)
        {
            if (!root) {
                mCurrent = nullptr;
                return;
            }
            leftmost(root);
            mCurrent = mStack.top();
            mStack.pop();
        };
        bool operator==(const Iterator& other) { return mCurrent == other.mCurrent; };
        bool operator!=(const Iterator& other) { return !(*this == other); };

        Iterator& operator++();
        std::pair<Key, Value&> operator*();

    private:
        Node* mCurrent;
        std::stack<Node*> mStack;

        void leftmost(Node* p);
    };

    Iterator begin() { return Iterator(mRoot); };
    Iterator end() { return Iterator(nullptr); };

private:
    class Node
    {
    public:
        //Constructors
        Node() : mKey(NULL), mPriority(rand()), mVal(0), mleftChild(nullptr), mrightChild(nullptr) {};
        Node(Key newKey) : mKey(newKey), mPriority(rand()), mVal(0), mleftChild(nullptr), mrightChild(nullptr) {};
        Node(Key newKey, Value i) : mKey(newKey), mPriority(rand()), mVal(i), mleftChild(nullptr), mrightChild(nullptr) {};
        Node(Key newKey, Node* parent): 
            mKey(newKey),
            mPriority(rand()),
            mVal(0),
            mleftChild(nullptr), 
            mrightChild(nullptr) {};
        
        // copy constructor
        Node(const Node& other) :
            mKey(other.mKey),
            mPriority(other.mPriority),
            mVal(other.mVal),
            mrightChild(other.mrightChild),
            mleftChild(other.mleftChild) {};

        //getters
        Key key() { return mKey; };
        Value& value() { return mVal; };
        Node* rightChild() { return mrightChild; };
        Node* leftChild() { return mleftChild; };
        
        int priority() { return mPriority; };
        void setleftChild(Node* node) { mleftChild = node; };
        void setrightChild(Node* node) { mrightChild = node; };
        
        Value& addKey(BST* tree, Key key);
        Node* resetPriority(std::stack<Node*> stack, BST* tree, Node* y);

    private:
        const Key mKey;
        const int mPriority;
        Value mVal;
        Node* mleftChild;
        Node* mrightChild;
        
        Value& findKey(std::stack<Node*> stack, BST* tree, Node* root, Key key);
        bool priorityHelper(Node* x, Node* y);
        void leftRotation(Node* x, Node* y);
        void rightRotation(Node* x, Node* y);
    };

    Node* mRoot;
    void printHelper(Node* root)const;
    void sideways(Node* current, int level) const ;
};
#endif