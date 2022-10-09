#include "IntTree.hpp"
#include <stdio.h>

IntTree* IntTree::insert(int val) {
	if (val < value) {
		if (left)
			left = left->insert(val);
		else {
			left = new IntTree();
			left->value = val;
		}
	}
	else {
		if (right)
			right = right->insert(val);
		else {
			right = new IntTree();
			right->value = val;
		}
	}
	return this;
}

IntTree* IntTree::remove(int val, IntTree* root) {
	if (val < value) 
		if (left)
			left = left->remove(val, root);
	else
		if (right)
			right = right->remove(val, root);

	if (value == val) {
		value = NULL;
		if (left) {
			IntTree* _left = left;
			int nuVal = _left->value;
			this->~IntTree();
			_left = _left->remove(_left->value, root);
			root->insert(nuVal);
		}
		if (right) {
			this->~IntTree();
			int value = right->value;
			right = right->remove(right->value, root);
			root->insert(value);
		}
		this->~IntTree();
	}
	return this;
}

void IntTree::print() {
	if (left)
		left->print();
	printf("%d ", value);
	if (right)
		right->print();
}

IntTree::~IntTree() {
}
