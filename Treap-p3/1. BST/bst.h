//-----------------------------------------------------
/*
Header file implementation referenced from class
Prof. Morris Bernstein
*/
//----------------------------------------------------

#ifndef BST_H
#define BST_H

#include <string>
#include <stack>

template<class Key, class Value>
class BST
{
    class Node;
public:
    BST() :mRoot(nullptr){};
    void displaySideways() const;
    Value& operator[](const Key& key);
    void print()const {  printHelper(mRoot);    };

    class Iterator {
    public:
        Iterator(Node* root);

        bool operator==(const Iterator& other) {
            return mCurrent == other.mCurrent;
        };
        bool operator!=(const Iterator& other) {
            return !(*this == other);
        };

        Iterator& operator++();
        const std::pair<const Key&, Value&> operator*()
        {
            return std::pair<const Key&, Value&>(mCurrent->key(), mCurrent->value());
        };

    private:
        void leftmost(Node* p);

        Node* mCurrent;
        std::stack<Node*> mStack;
    };

    Iterator begin() {
        return Iterator(mRoot);
    };
    Iterator end() {
        return Iterator(nullptr);
    };

private:
    class Node
    {
    public:
        Node() : mKey(NULL), mVal(0), mleftChild(nullptr), mrightChild(nullptr) {};
        Node(Key newKey) : mKey(newKey), mVal(0), mleftChild(nullptr), mrightChild(nullptr) {};
        Node(Key newKey, Value i) : mKey(newKey), mVal(i), mleftChild(nullptr), mrightChild(nullptr) {};
        
        // copy constructor
        Node(const Node& other) :
            mKey(other.mKey),
            mVal(other.mVal),
            mrightChild(other.mrightChild),
            mleftChild(other.mleftChild) {};

        Value& findKey(Key key);
        const Key& key() { return mKey; };
        Value& value() { return mVal; };
        Node* rightChild() { return mrightChild; };
        Node* leftChild() { return mleftChild; };
        
    private:
        const Key mKey;
        Value mVal;
        Node* mleftChild;
        Node* mrightChild;
    };

    Node* mRoot;
    void printHelper(Node* root)const
    {
        if (!root)
            return;
        printHelper(root->leftChild());
        std::cout << root->value() << " " << root->key() << std::endl;
        printHelper(root->rightChild());
    };
    void sideways(Node* current, int level) const;

};
#endif
