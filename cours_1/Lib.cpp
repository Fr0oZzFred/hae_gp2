#include"Lib.hpp"
#include<iostream>

void Lib::Memcpy(char* dest, const char* src, int size) {
	for (int i = 0; i < size; i++)
		dest[i] = src[i];
}

char* Lib::StrChr(const char* src, const char trg) {
	int srcLen = 0;
	while (src[srcLen] != 0) {
		srcLen++;
	}

	int len = 0;
	while (*src) {
		if (*src == trg) {
			char* ptr = new char[srcLen - len]; //YOLO
			int idx = 0;
			while (*src) {
				ptr[idx] = *src;
				*src++;
				idx++;
			}
			return ptr;
		}
		*src++;
		len++;
	}
	return nullptr;
}

char* Lib::StrStr(const char* src, const char* substr) {
	
	//Pourquoi je ne peux pas include StringFunctions ?
	int subLen = 0;
	while (substr[subLen] != 0) {
		subLen++;
	}

	int idx = 0;
	while (src[idx]) {
		if (src[idx] == substr[0]) {
			bool same = true;
			for (int i = 0; i < subLen; i++) {
				if (src[idx + i] != substr[i]) {
					same = false;
					break;
				}
			}
			char* ptr = new char[20]; //YOLO
			if (same) {
				for (int i = 0; i < idx; i++) {
					*src++;
				}
				int i = 0;
				while (*src) {
					ptr[i] = *src;
					i++;
					*src++;
				}
				return ptr;
			}
		}
		idx++;
	}
	return nullptr;
}
