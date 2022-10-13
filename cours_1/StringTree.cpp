#include "StringTree.hpp"
#include <iostream>
StringTree* StringTree::insert(char* val) {
//	if (val < value) {
//		if (left)
//			left = left->insert(val);
//		else {
//			left = new StringTree();
//			left->value = val;
//		}
//	}
//	else {
//		if (right)
//			right = right->insert(val);
//		else {
//			right = new StringTree();
//			right->value = val;
//		}
//	}
	return this;
}

StringTree* StringTree::remove(char* val) {
	return nullptr;
}

void StringTree::print() {
	if (left)
		left->print();
	printf("%d ", value);
	if (right)
		right->print();
}
