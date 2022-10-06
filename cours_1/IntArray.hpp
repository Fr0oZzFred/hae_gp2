#pragma once
#include <iostream>
class IntArray {
public:
	IntArray(int maxsize);
	int get(int idx);
	void set(int idx, int value);
	void resize(int nuSize);
	~IntArray();
	int searchOrderInferior(int val);
	void shiftRight(int idx);
	void insertOrderInferior(int val);
	bool isSorted();
	void Sort();
	static int compAscending(const void* elem1, const void* elem2);
	static int compDescending(const void* elem1, const void* elem2);
	int getSize();
protected:
	int* data = nullptr;
	int size = 0;
};