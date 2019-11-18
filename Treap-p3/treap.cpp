#include "treap.h"
#include <iostream>


//************************ BST :: Iterator ***********************************
template<typename Key, typename Value>
typename BST<Key, Value>::Iterator & BST<Key, Value>::Iterator::operator++()
{
    leftmost(mCurrent->rightChild());
    if (mStack.empty()) {
        mCurrent = nullptr;
        return *this;
    }
    mCurrent = mStack.top();
    mStack.pop();
    return *this;
}

template<typename Key, typename Value>
 std::pair<Key, Value&> BST<Key, Value>::Iterator::operator*()
{
    return  std::pair<Key, Value&>(mCurrent->key(), mCurrent->value());
}

template<typename Key, typename Value>
void BST<Key, Value>::Iterator::leftmost(Node * p)
{
    while (p)
    {
        mStack.push(p);
        p = p->leftChild();
    }
}
//****************  BST:: NODE **********************************************//
/*
//the add key method was added at a public level to create a stack before the
//key can be found. This enables parents to be tracked without the use of a
//parent pointer
*/
template<typename Key, typename Value>
Value & BST<Key, Value>::Node::addKey(BST * tree, Key key)
{
    std::stack<Node*> tempStack;
    return findKey(tempStack, tree, tree->mRoot, key);
}

/*
//the stack is use to save the parent node everytime the tree is traversed.
and resetPriority is called to balance the tree.
*/
template<typename Key, typename Value>
Value & BST<Key, Value>::Node::findKey(std::stack<Node*> stack, BST * tree, Node * root, Key key)
{
    stack.push(root);

    if (key == mKey)
        return mVal;

    if (key < mKey)
        if (!mleftChild)
        {
            mleftChild = new Node(key, root);
            Node* node = resetPriority(stack, tree, mleftChild);
            return node->mVal;
        }
        else
            return mleftChild->findKey(stack, tree, mleftChild, key);
    else
        if (!mrightChild)
        {
            mrightChild = new Node(key, root);
            Node* node = resetPriority(stack, tree, mrightChild);
            return node->mVal;
        }
        else
            return mrightChild->findKey(stack, tree, mrightChild, key);
}

/*
the tree comes in as a pointer if the root has tobe changed. And the added new node-y
is retained a reference to be sent back to findkey so that its value can be updated on return
*/
template<typename Key, typename Value>
typename BST<Key, Value>::Node * BST<Key, Value>::Node::resetPriority(std::stack<Node*> stack, BST * tree, Node * y)
{
    bool isSwap = false;
    while (!stack.empty())
    {
        Node* x = stack.top();
        stack.pop();
        if (isSwap)
        {
            if (y->key() < x->key())
                x->setleftChild(y);
            else
                x->setrightChild(y);
        }
        isSwap = priorityHelper(x, y);

        if (isSwap && tree->mRoot == x)
            tree->setRoot(y);
    }
    return y;
}
/*
returns a bool so the parent node can be set to the correct node if a swap was made.
*/
template<typename Key, typename Value>
bool BST<Key, Value>::Node::priorityHelper(Node * x, Node * y)
{
    if (x->priority() < y->priority())
    {
        if (x->key() < y->key())
            leftRotation(x, y);
        else
            rightRotation(x, y);
        return true;
    }
    return false;
}

template<typename Key, typename Value>
void BST<Key, Value>::Node::leftRotation(Node * x, Node * y)
{
    x->setrightChild(y->leftChild());
    y->setleftChild(x);
}

template<typename Key, typename Value>
void BST<Key, Value>::Node::rightRotation(Node * x, Node * y)
{
    x->setleftChild(y->rightChild());
    y->setrightChild(x);
}

//*********************  BST *********************************************//
template<typename Key, typename Value>
Value & BST<Key, Value>::operator[](const Key & key)
{
    if (!mRoot)
    {
        mRoot = new Node(key, nullptr);
        return mRoot->value();
    }
    return mRoot->addKey(this, key);
}

template<typename Key, typename Value>
void BST<Key, Value>::printHelper(Node * root) const
{
    if (!root)
        return;
    printHelper(root->leftChild());
    std::cout << root->value() << " " << root->key() << std::endl;
    printHelper(root->rightChild());
}
//---------------------------------------------------------------------------
// displaySideways 
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.

//Source: Prof. Zander's Lab2 Assignment Question
//--------------------------------------------------------------------------

template<typename Key, typename Value>
void BST<Key, Value>::sideways(Node * current, int level) const
{
if (current != NULL) {
    level++;
    sideways(current->rightChild(), level);

    // indent for readability, 4 spaces per depth level
    for (int i = level; i >= 0; i--) {
        std::cout << "    ";
    }

    std::cout << current->key() << ":" << current->priority() << std::endl;        // display information of object
    sideways(current->leftChild(), level);
}
    }