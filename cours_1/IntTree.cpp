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

IntTree* IntTree::remove(int val) {
	if (val < value) 
		if (left)
			left = left->remove(val);
	else
		if (right)
			right = right->remove(val);

	if (value == val) {
		delete this;
		return nullptr;
		if (left) {
			left = left->remove(left->value);
		}
		if (right) {
			right = right->remove(right->value);
		}
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
