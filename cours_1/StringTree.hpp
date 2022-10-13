#pragma once
class StringTree {
public:
	char* value;
	StringTree* left;
	StringTree* right;

	StringTree* insert		(char* val);
	StringTree* remove		(char* val);
	bool searchMatch		(char* val);
	void print();
	int compare				(char* val);
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

	bool searchMatch(char* val) {
		return root->searchMatch(val);
	}
};