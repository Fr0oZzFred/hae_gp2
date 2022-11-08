#pragma once
#include <cstdint>
#include <cstdlib>
#include <algorithm>
#include <random>
#include <ctime>
#include <stdlib.h>

//Predicat ordre partiel <=
class Int64Array {
public:
	int64_t* data;
	int allocSize;
	int cursor;

public:
	Int64Array(int _allocSize);
	~Int64Array();
	int size();
	void ensure(int size);//s’assure que le tableau fait au moins size
	void push_back(int64_t elem);
	void push_front(int64_t elem);
	void insert(int pos, int64_t elem);//coder memcpy/memmoveen rec?  inserer et decaller
	void set(int pos, int64_t elem);
	int64_t get(int pos);

	void fillWithRandom(int nbElem);
	int searchPosition(int elem);
	void removeOne(int elem);
	void removeAll(int elem);
	void InsertionSort();
	void Qsort();
	int bsearch(int64_t val);
	int linearsearch(int64_t val);

	static Int64Array* sort(Int64Array& ref);
protected:
	static int compare(const void* val1, const void* val2);
	int bsearch(int start, int end, int64_t val);
	void AddElementsInOrderedArray(Int64Array& ref, int idx);
	int searchOrderPos(int elem);
	int searchBetween(int elem, int idx = 0);
	int searchPosition(int elem, int idx);
	bool removeOne(int elem, int idx);
	void removeAll(int elem, int idx);
	void shift_left(int from, int to);
	void shift_right(int from, int to);
	void setZero(int start, int end);
	void set_unsafe(int pos, int64_t elem);
	int64_t get_unsafe(int pos);
	static int rand() {
		static bool isInit = false;
		if (!isInit) {
			clock_t now = clock();
			srand(now);
			isInit = true;
		}
		return ::rand();
	}
};