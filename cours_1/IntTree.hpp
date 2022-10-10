#pragma once

class IntTree {
public:
	int			value = 0;
	IntTree*	left = nullptr;
	IntTree*	right = nullptr;

	IntTree*	insert(int val);
	IntTree*	remove(int val);
	void		print();
};

class IntTreeController {
public:


	IntTree* root = nullptr;

	void insert(int val) {
		if (!root) {
			root = new IntTree();
			root->value = val;
		}
		else {
			root = root->insert(val);
		}
	};

	void remove(int val) {
		root = root->remove(val);
	};

	void print() {
		if (root)
			root->print();
	}
};