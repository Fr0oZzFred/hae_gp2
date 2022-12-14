#pragma once
class Lib {
public:
	static void Memcpy(char* dest, const char* src, int size);
	static void MemcpyRec(char* dest, const char* src, int size);
	static const char* StrChr(const char* src, const char c);
	static const char* StrChrRec(const char* src, const char c);
	static const char* StrStr(const char* src, const char* substr);
	static const char* StrStrRec(const char* src, const char* substr);
	static bool StrPrefix(const char* src, const char* tok);
	static int add(int a, int b);
	static int sub(int a, int b);
	static int mul(int a, int b);
	static int div(int a, int b);
	static int mod(int a, int b);
	static int StrlenRec(const char* str);
	static void StrcpyRec(char* dest, const char* src);
	static void StrncpyRec(char* dest, const char* src, int size);
	static void ZeroMemory(char* dest, int size);
	static int StrCmp(const char* str1, const char* str2);
	static int mulTerminalRecursion(int a, int b, int res);
	static int divTerminalRecursion(int a, int b, int res);
};