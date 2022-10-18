#pragma once
#include <string>
#include <iostream>

class StringTreeCorrection {
public:
	std::string				value;
	StringTreeCorrection*	left = nullptr;
	StringTreeCorrection*	right = nullptr;

	StringTreeCorrection*	insert(std::string &val);
	StringTreeCorrection*	remove(std::string &val);
	StringTreeCorrection*	searchString(std::string &val);
	StringTreeCorrection*	searchPattern(std::string &val);
	void					print();
};

class StringTreeControllerCorrection {
public:

	StringTreeCorrection* root = nullptr;

	void insert(std::string val) {
		if (!root) {
			root = new StringTreeCorrection();
			root->value = val;
		}
		else
			root = root->insert(val);
	};

	void remove(std::string val) {
		root = root->remove(val);
	};

	void print() {
		if (root) {
			root->print();
			std::cout << "\n";
		}
		else {
			std::cout << "[]\n";
		}
	};

	StringTreeCorrection* searchString(std::string& val) {
		if (root)
			return root->searchString(val);
		else
			return nullptr;
	};

	StringTreeCorrection* searchPattern(std::string& val) {
		if (root)
			return root->searchPattern(val);
		else
			return nullptr;
	};
};