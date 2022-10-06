#include "LinkedListInt.hpp"
#include <iostream>
void LinkedListInt::insert(int val) {
	EntryInt* nuVal = new EntryInt;
	nuVal->value = val;

	if (!root) {
		root = nuVal;
	}
	else {
		auto oldRoot = root;
		root = nuVal;
		oldRoot->prev = root;
		root->next = oldRoot;
	}
};

void LinkedListInt::remove(int val) {
	auto cur = root;
	while (cur) {
		auto prev = cur->prev;
		auto next = cur->next;
		if (cur->value == val) {
			if (prev) prev->next = next;
			if (next) next->prev = prev;
			if (root == cur)
				root = next;
			cur->~EntryInt();
			cur = nullptr;
		}
		cur = next;
	}
};

void LinkedListInt::print() {
	auto cur = root;
	while (cur) {
		printf("%d ", cur->value);
		cur = cur->next;
	}
	printf("\n");
};