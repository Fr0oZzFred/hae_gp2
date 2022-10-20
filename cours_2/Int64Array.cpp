#include "Int64Array.hpp"
Int64Array::Int64Array(int _allocSize) {
	if (_allocSize <= 0) _allocSize = 16;
	data = (int64_t*)malloc(_allocSize * sizeof(int64_t));
	setZero(0, _allocSize);
	cursor = 0;
	allocSize = _allocSize;
};

Int64Array::~Int64Array() {
	free(data);
	data = nullptr;
}

void Int64Array::ensure(int size) {
	if (size <= allocSize) return;
	int toAlloc = std::max<int>(allocSize * 1.5f, size);
	data = (int64_t*)realloc(data, toAlloc * sizeof(int64_t));
	allocSize = toAlloc;
	setZero(cursor, toAlloc);
}


void Int64Array::push_back(int64_t elem) {
	ensure(cursor + 1);
	data[cursor] = elem;
	cursor++;
}

void Int64Array::push_front(int64_t elem) {
	ensure(cursor + 1);
	cursor++;
	//while data[cursor] = data[cursor-1]; Créer sous function
}
void Int64Array::insert(int pos, int64_t elem) {
	if (cursor == 0) set(0, elem);
}

void Int64Array::set(int pos, int64_t elem) {
	data[pos] = elem;
}


void Int64Array::setZero(int start, int end) {
	if (start >= end) return;
	data[start] = 0;
	setZero(start + 1, end);
}

void Int64Array::set_unsafe(int pos, int64_t elem) {
}
