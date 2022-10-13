#include "StringTree.hpp"
#include <iostream>
StringTree* StringTree::insert(char* val) {
	if (compare(val)) {
		if (left)
			left = left->insert(val);
		else {
			left = new StringTree();
			left->value = val;
		}
	}
	else {
		if (right)
			right = right->insert(val);
		else {
			right = new StringTree();
			right->value = val;
		}
	}
	return this;
};

StringTree* StringTree::remove(char* val) {
	if (val == value) {
		auto oldLeft = left;
		auto oldRight = right;

		if (!oldRight && !oldLeft) {
			delete this;
			return nullptr;
		}
		else if (!oldRight) {
			delete this;
			return oldLeft;
		}
		else if (!oldLeft) {
			delete this;
			return oldRight;
		}
		while (left) {
			auto lval = left->value;
			left = left->remove(lval);
			right->insert(lval);
		}
		return right;
	}
	if (left && (val <= value)) left = left->remove(val);
	if (right && (val >= value)) right = right->remove(val);
	return this;
};

void StringTree::print() {
	if (left)
		left->print();
	printf("%s ", value);
	if (right)
		right->print();
};

//False = val est sup�rieur
bool StringTree::compare(char* val) {
	int idx = 0;
	int len = 0;
	int len1 = 0;
	while (value[len] != 0) {
		len++;
	}
	while (val[len1] != 0) {
		len1++;
	}
	int minLen = len < len1 ? len : len1;
	for (int i = 0; i < minLen; i++) {
		if		(value[i] < val[i])		return false;
		else if (value[i] > val[i])		return true;
	}
	return true;
};
