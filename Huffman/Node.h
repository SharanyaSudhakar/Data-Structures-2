#ifndef NODE_H
#define NODE_H

template <typename Data, typename Priority>
class Node
{
public:
    //constructors
    Node() : mData(), mPriority(), mLeft(nullptr), mRight(nullptr) {};
    Node(Priority freq) : mData(), mPriority(freq), mLeft(nullptr), mRight(nullptr) {};
    Node(Data data, Priority freq) : mData(data), mPriority(freq), mLeft(nullptr), mRight(nullptr) {};
    Node(Priority freq, Node<Data,Priority>* left, Node<Data, Priority>* right) :
        mData(), mPriority(freq), mLeft(left), mRight(right) {};
    Node(const Node& newnode) : 
        mData(newnode.data()), 
        mPriority(newnode.priority()), 
        mLeft(newnode.mLeft), 
        mRight(newnode.mRight) {};

    //getters
    Priority priority() const { return mPriority; }
    Data data() const { return mData;}
    Node<Data, Priority>* left() const { return mLeft; }
    Node<Data, Priority>* right() const { return mRight; }
    void setLeft(Node<Data, Priority>* node) { mLeft = node; };
    void setRight(Node<Data, Priority>* node) { mRight = node; };

    //setters
    void setPriority(Priority freq) { 
        if(freq>=0)
            mPriority = freq; 
    };
    void setData(Data d) { mData = d; }

    //operators
    bool operator< (const Node& other) const {
        return (mPriority < other.priority());
    };

private:
    Data mData;
    Priority mPriority;
    Node<Data, Priority>* mLeft;
    Node<Data, Priority>* mRight;
};
#endif