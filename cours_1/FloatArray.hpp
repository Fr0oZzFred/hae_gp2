#pragma once
#include <atomic>
#include <functional>

class FloatArray {
public:

	FloatArray(int _size);
	FloatArray(const FloatArray& from);
	~FloatArray();
	void resize(int nuSize);
	void push_first(float val);
	void push_back(float val);
	void set(int idx, int val);
	float get(int idx);
	int getSize();
	float* getData();
	void print();
	void iter(std::function<void(float)> f);

	static FloatArray fromArray(float* data, int len);

protected:
	float*	data = nullptr;
	int		allocSize = 0;
	int		current = 0;
};