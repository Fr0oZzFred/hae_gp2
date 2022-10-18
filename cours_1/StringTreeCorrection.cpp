#include "StringTreeCorrection.hpp"
#include "Lib.hpp"
#include <stdio.h>

StringTreeCorrection* StringTreeCorrection::insert(std::string &val) {
	if (val < value) {
		if (left)
			left = left->insert(val);
		else {
			left = new StringTreeCorrection();
			left->value = val;
		}
	}
	else {
		if (right)
			right = right->insert(val);
		else {
			right = new StringTreeCorrection();
			right->value = val;
		}
	}
	return this;
}

StringTreeCorrection* StringTreeCorrection::remove(std::string &val) {
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
}

StringTreeCorrection* StringTreeCorrection::searchString(std::string& val) {
	if(val == value) return this;

	if(left)
	if (val < value) {
		auto res = left->searchString(val);
		if (res)
			return res;
	}
	if(right)
	if (val > value) {
		auto res = right->searchString(val);
		if (res)
			return res;
	}
	return nullptr;
}

StringTreeCorrection* StringTreeCorrection::searchPattern(std::string& val) {
	auto res = Lib::StrStr(value.c_str(), val.c_str());
	if (res) return this;
	else {
		if (left) {
			auto res = left->searchPattern(val);
			if (res) return res;
		}
		if (right) {
			auto res = right->searchPattern(val);
			if (res) return res;
		}
	}
	return nullptr;
}

void StringTreeCorrection::print() {
	if (left)
		left->print();
	//printf("%s ", value.c_str());
	std::cout << value << " ";
	if (right)
		right->print();
}
