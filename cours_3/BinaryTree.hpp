#pragma once
#include <string>

template<typename Type>
class BNode {
public:
	Type key;
	BNode * left = nullptr;
	BNode * right = nullptr;

	BNode<Type> * insert(Type val);
	BNode<Type> * remove(Type val);
	void print();
	int size();

	BNode(Type _key, BNode<Type>* _left = nullptr, BNode<Type>* _right = nullptr) {
		key = _key;
		left = _left;
		right = _right;
	};

	~BNode() {
		cout << "Deleted";
	};
};


template<typename Type>
class BinaryTree {
public:
	BNode<Type>* head = nullptr;

	void insert(Type val);
	void print();
	void remove(Type val);
	int size();
};

typedef BinaryTree<int> IntTree;
typedef BinaryTree<float> FloatTree;
typedef BinaryTree<std::string> StringTree;

template<typename Type>
void BinaryTree<Type>::insert(Type val) {
	if (!head) {
		head = new BNode<Type>(val);
		return;
	}

	head->insert(val);
}
template<typename Type>
void BinaryTree<Type>::print() {
	if (!head) {
		cout << "[ ]";
		return;
	}
	cout << "[ ";
	head->print();
	cout << "]";
}
template<typename Type>
void BinaryTree<Type>::remove(Type val) {
	if (head) {
		head->remove(val);
	}
}
template<typename Type>
inline int BinaryTree<Type>::size() {
	if (head) return head->size();
};

template<typename Type>
BNode<Type>* BNode<Type>::insert(Type val) {
	if (val < key) {
		if (left)
			left = left->insert(val);
		else
			left = new BNode(val);
	}
	else {
		if (right)
			right = right->insert(val);
		else
			right = new BNode(val);
	}
	return this;
}
template<typename Type>
BNode<Type>* BNode<Type>::remove(Type val) {
	auto tLeft = left;
	auto tRight = right;
	if (key == val) {
		delete this;
		if (!tLeft && !tRight) return nullptr;
		else if (!tLeft) return tRight;
		else if (!tRight) return tLeft;
		else {
			while (tLeft) {
				auto tKey = tLeft->key;
				tRight = tRight->insert(tKey);
				tLeft = tLeft->remove(tKey);
			}
			return tRight;
		}
	}
	else {
		if (val < key) {
			if (left) left->remove(val);
		}
		else {
			if (right) right->remove(val);
		}
		return this;
	}
};
template<typename Type>
void BNode<Type>::print() {
	if (left)
		left->print();
	cout << key << " ";
	if (right)
		right->print();
}
template<typename Type>
int BNode<Type>::size() {
	int sz = 1;
	if (left)
		sz += left->size();
	if (right)
		sz += right->size();
	return sz;
};