#include"Lib.hpp"
#include<iostream>

void Lib::Memcpy(char* dest, const char* src, int size) {
	for (int i = 0; i < size; i++)
		dest[i] = src[i];
}

char* Lib::StrChr(const char* src, const char trg) {
	do {
		if (*src == trg) {
			printf(src);
			printf("\n");
			//return nuStr;
		}
	} while (*src++);
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
				}
			}
			printf("\n");
			printf("%d", same);
		}
		idx++;
	}
	return nullptr;
}
