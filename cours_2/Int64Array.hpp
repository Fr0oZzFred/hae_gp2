#pragma once
#include <cstdint>
#include <cstdlib>
#include <algorithm>
//Predicat ordre partiel <=
class Int64Array {
public:
	int64_t* data;
	int allocSize;
	int cursor;

public :
	Int64Array(int _allocSize);
	~Int64Array();
	void ensure(int size);//s’assure que le tableau fait au moins size
	void push_back(int64_t elem);
	void push_front(int64_t elem);
	void insert(int pos, int64_t elem);//coder memcpy/memmoveen rec?  inserer et decaller
	void set(int pos, int64_t elem);

protected:
	void setZero(int start, int end);
	void set_unsafe(int pos, int64_t elem);
};