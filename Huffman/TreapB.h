// BST- TREAP
// Used Theses Websites for reference on how to rotate in a treap
// https://www.geeksforgeeks.org/treap-a-randomized-binary-search-tree/
//http://jeffe.cs.illinois.edu/teaching/algorithms/notes/10-treaps.pdf
//https://www.cs.cornell.edu/courses/cs312/2003sp/lectures/lec26.html



#if !defined(Treap_H)
#define Treap_H
#include <stack>
#include <string>
#include <utility>
#include <iostream>

template <class Key, class Value>
class Treap {

private:
	class Node {
	public:
		Node(Key key);
		const Key& key();
		Value& value();
		const int& priority();
		Node*& left();
		Node*& right();
	private:
		const Key key_;
		Value value_;
		Node* left_;
		Node* right_;
		int priority_;
	};
public:
	Value& operator[](const Key& key);
	class Iterator;
	Treap();
	Iterator begin();
	Iterator end();
	class Iterator {
	public:
		Iterator(Node* root);
		bool operator==(const Iterator& other);
		bool operator!=(const Iterator& other);
		Iterator& operator++();
		const std::pair<const Key&, Value&> operator*();
	private:
		void leftmost(Node* p);
		Node* current_;
		std::stack<Node*> stack_;
	};

	Node* root_;
	Node* rotateRight(Node* current);
	Node* rotateLeft(Node* current);
	Node* lookup(Node* curr, Node*& item, const Key& key);
	void dump(Node* current, int height);
	void display();
};


template <class Key, class Value>
Treap<Key, Value>::Treap() : root_(nullptr) {}

template <class Key, class Value>
Value& Treap<Key,Value>::operator[](const Key& key) {
	Node* item_ = nullptr;
	this->root_ = this->lookup(this->root_, item_, key);
	return item_->value();
}
template <class Key, class Value>
Treap<Key,Value>::Node::Node(Key key) : key_(key), value_(), left_(nullptr), right_(nullptr) {
	this->priority_ = rand();

}

template <class Key, class Value>
const Key& Treap<Key,Value>::Node::key() { return key_; }

template <class Key, class Value>
Value& Treap<Key,Value>::Node::value() { return value_; }

template <class Key, class Value>
typename Treap<Key,Value>::Node* Treap<Key,Value>::lookup(Node* curr, Node*& item, const Key& key) {
	if (curr == nullptr) {
		curr = new Node(key);
		item = curr;
		return curr;
	}

	if (curr->key() == key) {
		item = curr;
	}
	else if (curr->key() > key) {
		curr->left() = this->lookup(curr->left(), item, key);
		if (curr->left()->priority() < curr->priority()) {
			curr = this->rotateRight(curr);
		}
	}
	else {
		curr->right() = this->lookup(curr->right(), item, key);
		if (curr->right()->priority() < curr->priority()) {
			curr = this->rotateLeft(curr);
		}
	}
	return curr;
}

template <class Key, class Value>
typename Treap<Key,Value>::Node*& Treap<Key,Value>::Node::left() { return this->left_; }

template <class Key, class Value>
typename Treap<Key, Value>::Node*& Treap<Key, Value>::Node::right() { return this->right_; }

template<class Key, class Value>
const int& Treap<Key, Value>::Node::priority() {
	return this->priority_;
}

template <class Key, class Value>
typename Treap<Key, Value>::Iterator Treap<Key, Value>::begin() {
	return Treap<Key,Value>::Iterator(root_);
}

template <class Key, class Value>
typename Treap<Key, Value>::Iterator Treap<Key, Value>::end() {
	return Treap<Key,Value>::Iterator(nullptr);
}
template <class Key, class Value>
Treap<Key, Value>::Iterator::Iterator(Node* root) {
		if (!root) {
			current_ = nullptr;
			return;
		}
		leftmost(root);
		current_ = stack_.top();
		stack_.pop();
}

template <class Key, class Value>
bool Treap<Key, Value>::Iterator::operator==(const Iterator& other) {
	return current_ = other.current_;
}

template <class Key, class Value>
bool Treap<Key,Value>::Iterator::operator!=(const Iterator& other) {
	return !(this->current_ == other.current_);
}

template <class Key, class Value>
typename Treap<Key, Value>::Iterator& Treap<Key,Value>::Iterator::operator++() {
		leftmost(current_->right());
		if (stack_.empty())
		{
			current_ = nullptr;
			return *this;
		}
		current_ = stack_.top();
		stack_.pop();
		return *this;
}

template <class Key, class Value>
void Treap<Key, Value>::Iterator::leftmost(Node* p) {
			while (p) {
				stack_.push(p);
				p = p->left();
			}
}

template <class Key, class Value>
 const std::pair<const Key&, Value&> Treap<Key, Value>::Iterator::operator*() {
	return std::pair<const Key&, Value&>(current_->key(), current_->value());
}

 template <class Key, class Value>
 typename Treap<Key, Value>::Node* Treap<Key, Value>::rotateRight(Node* current) {
	 Node* left = current->left();
	 current->left() = current->left()->right();
	 left->right() = current;
	 return left;
 }


 template <class Key, class Value>
 typename Treap<Key, Value>::Node* Treap<Key, Value>::rotateLeft(Node* current) {
	 Node* right = current->right();
	 current->right() = current->right()->left();
	 right->left() = current;
	 return right;
 }

 template <class Key, class Value>
 void Treap<Key, Value>::dump(Node* current, int height) {
	 if (current != nullptr) {
		 dump(current->right(), height + 1);
		 for (int i = 0; i < height; i++) {
			 std::cerr << "\t";
		 }
		 std::cerr << current->key() << " " << current->value() << " " <<
			 current->priority() << std::endl;
		 dump(current->left(), height + 1);
	 }
 }

 template <class Key, class Value>
 void Treap<Key, Value>::display() {
	 this->dump(this->root_, 0);
 }
#endif