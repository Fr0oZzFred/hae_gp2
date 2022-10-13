#pragma once
class Lib {
public:
	static void Memcpy(char* dest, const char* src, int size);
	static char* StrChr(const char* src, const char trg);
	static char* StrStr(const char* src, const char* substr);
};