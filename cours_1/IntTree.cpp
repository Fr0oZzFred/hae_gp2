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
	if (val < value) {
		if (left)
			left = left->remove(val);
	}
	else {
		if (right)
			right = right->remove(val);
	}

	if (value == val) {
		if (!left && !right) {
		delete this;
		return nullptr;
		}
		if (left) {
			value = left->value;
			left->value = val;
			left = left->remove(val);
		}
		if (right) {
			value = right->value;
			right->value = val;
			right = right->remove(val);
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
