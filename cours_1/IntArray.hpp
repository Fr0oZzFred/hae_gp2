#pragma once
#include <iostream>
class IntArray {
public:

	IntArray(int maxsize) {
		size = maxsize;
		//data = (int*) malloc(size * sizeof(int)); c style
		data = new int[maxsize]; // c++ style
		for (int i = 0; i < size; i++) {
			data[i] = 0; // == *(data + i) = 0;
		}
	};

	int get(int idx) {
		if (idx < 0) throw "out of bounds, less than 0";
		if (idx >= size) throw "out of bounds, more than " + size;
		return data[idx]; // == return *(data + idx);
	};

	void set(int idx, int value) {
		if (idx < 0) throw "out of bounds, less than 0";
		if (idx >= size) throw "out of bounds, more than " + size;
		data[idx] = value; // == *(data + idx) = value;
	};

	void resize(int nuSize) {
		if (nuSize == size)
			return;

		bool grow = nuSize > size;

		auto ndata = new int[nuSize];
		for (int i = 0; i < nuSize; ++i)
			ndata[i] = 0;

		int targetSize = (grow) ? size : nuSize;
		for (int i = 0; i < targetSize; ++i)
			ndata[i] = data[i];

		int* odata = data;
		data = ndata;
		size = nuSize;
		delete[]odata;
	};

	~IntArray() {
		//free(data); // c style
		delete[] data; //c++ Style
		size = 0;
	};

	//Tableau est trié
	int searchOrderInferior(int val) {
		int idx = 0;
		while ((data[idx] < val) && (idx < size)) {
			idx++;
		}
		return idx;
	};

	//Warning this function breaks the invariant by inserting a sentient
	void shiftRight(int idx) {
		if ((idx < 0) || (idx >= size))
			return;
		for (int i = size - 1; i > idx; --i)
			data[i] = data[i - 1];
		data[idx] = 0;
	};

	//Invariant : mon tableau est trié
	void insertOrderInferior(int val) {
		int idx = searchOrderInferior(val);
		resize(getSize() + 1);
		shiftRight(idx);
		data[idx] = val;
	}

	bool isSorted() {
		for (int i = 0; i < size - 1; i++)
			if (data[i] > data[i + 1]) return false;
		return true;
	};

	void Sort() {
		qsort(data, size, sizeof(int), compAscending);
	};

	static int compAscending(const void* elem1, const void* elem2) {
		int* x = (int*)elem1;
		int* y = (int*)elem2;
		//(int)elem1 = l'adresse de elem1 converti en int

		//on pourrait faire
		//int xValue = *x;
		//int yValue = *y;
		//return xValue - yValue;

		return *x - *y;
	}

	static int compDescending(const void* elem1, const void* elem2) {
		int* x = (int*)elem1;
		int* y = (int*)elem2;
		return *y - *x;
	}

	int getSize() {
		return size;
	};


protected:
	int* data = nullptr;
	int size = 0;
};