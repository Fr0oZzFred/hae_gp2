#pragma once
class StringTree {
public:
	char* value;
	StringTree* left;
	StringTree* right;

	StringTree* insert(char* val);
	StringTree* remove(char* val);
	void print();
	bool compare(char* val);
};

class StringTreeController {
public:
	StringTree* root = nullptr;

	void insert(char* val) {
		if (!root) {
			root = new StringTree();
			root->value = val;
		}
		else {
			root = root->insert(val);
		}
	};

	void remove(char* val) {
		root = root->remove(val);
	};

	void print() {
		if (root)
			root->print();
	}

};