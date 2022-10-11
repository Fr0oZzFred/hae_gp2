#include"FloatArray.hpp"
#include <xlocinfo>


FloatArray::FloatArray(int _size) {
	allocSize = _size;
	data = (float*)malloc(allocSize * sizeof(float));
	for (int i = 0; i < allocSize; i++)
		data[i] = 0;
};
FloatArray::FloatArray(const FloatArray& from) {
	resize(from.current);
	current = from.current;
	for (int i = 0; i < current; i++) {
		data[i] = from.data[i];
	}
}

FloatArray::~FloatArray() {
	free(data);
}
void FloatArray::resize(int nuSize) {
	if (nuSize < allocSize) return;

	data = (float*)realloc(data, nuSize * sizeof(float));
	for (int i = allocSize; i < nuSize; i++)
		data[i] = 0;

	allocSize = nuSize;
};
void FloatArray::push_first(float val) {
	if (current >= allocSize - 1)
		resize(allocSize + 1);
	resize(allocSize + 1);
	for (int i = current; i > 0; i--) {
		data[i] = data[i - 1];
	}
	data[0] = val;
	current++;
};
void FloatArray::push_back(float val) {
	resize(allocSize + 1);
	data[current++] = val;
};
void FloatArray::set(int idx, int val) {
	if (idx < 0) throw "less than 0";
	if (idx >= current) throw "out of bound";
	data[idx] = val;
};
float FloatArray::get(int idx) {
	if (idx < 0) throw "less than 0";
	if (idx >= current) throw "out of bound";
	return data[idx];
}
int FloatArray::getSize() {
	return current;
}
float* FloatArray::getData() {
	return data;
}
;
void FloatArray::print() {
	for (int i = 0; i < getSize(); ++i) {
		printf("%d => %f ", i, get(i));
	}
	printf("\n");
};
void FloatArray::iter(std::function<void(float)> f) {
	for (int i = 0; i < getSize(); ++i) {
		f(data[i]);
	}
};
FloatArray FloatArray::fromArray(float* data, int len) {
	FloatArray copy(len);
	for (int i = 0; i < len; i++) {
		copy.push_back(data[i]);
	}
	return copy;
};
