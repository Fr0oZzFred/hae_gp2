#include"Lib.hpp"

void Lib::Memcpy(char* dest, const char* src, int size) {
	for (int i = 0; i < size; i++)
		dest[i] = src[i];
}