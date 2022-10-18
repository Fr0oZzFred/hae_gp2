#pragma once
class Lib {
public:
	static void Memcpy(char* dest, const char* src, int size);
	static void MemcpyRec(char* dest, const char* src, int size);
	static const char* StrChr(const char* src, const char c);
	static const char* StrChrRec(const char* src, const char c);
	static const char* StrStr(const char* src, const char* substr);
	static const char* StrStrRec(const char* src, const char* substr);
};