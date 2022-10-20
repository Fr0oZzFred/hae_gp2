#include"Lib.hpp"
#include "StringFunctions.hpp"
void Lib::Memcpy(char* dest, const char* src, int size) {
	for (int i = 0; i < size; i++)
		dest[i] = src[i];
};

void Lib::MemcpyRec(char* dest, const char* src, int size) {
	if (size > 0) {
		*dest = *src;
		Memcpy(dest+1, src+1, size-1);
	}
};

//Renvoie nullptr si le char c n'est pas trouvé
//Sinon renvoie le ptr vers là où est le character
const char* Lib::StrChr(const char* src, const char c) {
	while (*src && (*src != c))
		src++;
	if (!*src)
		return nullptr;
	return src;
};

const char* Lib::StrChrRec(const char* src, const char c) {
	if (!*src)return nullptr;
	if (*src != c) return StrChrRec(src + 1, c);
	return src;
};

const char* Lib::StrStr(const char* src, const char* substr) {
	int subLen = Strlen(substr);

	int idx = 0;
	while (*src) {
		if (*src == substr[0]) {
			bool same = true;
			for (int i = 1; i < subLen; i++) {
				src++;
				if (*src != substr[i]) {
					same = false;
				}
			}
			if (same) return substr;
			src -= subLen - 1;
		}
		src++;
	}
	return nullptr;
};

const char* Lib::StrStrRec(const char* src, const char* substr) {
	if (!*src) return nullptr;
	if (StrPrefix(src, substr)) return substr;
	return StrStrRec(src + 1, substr);
}
bool Lib::StrPrefix(const char* src, const char* tok) {
	int i = 0;
	while (tok[i]) {
		if (tok[i] != src[i])
			return false;
		else
			i++;
	}
	return true;
}
int Lib::add(int a, int b) {
	if (b == 0) return a;
	if (a == 0) return b;

	if (b < 0) return add(a-1, b+1);
	return add(a+1, b-1);
}
int Lib::sub(int a, int b) {
	return add(a, -b);
}
int Lib::mul(int a, int b) {
	if((a == 0) || (b == 0)) return 0;
	if (a == 1) return b;
	if (b == 1)	return a;
	if (b > 0)	return add(a, mul(a, b - 1));
				return add(b, mul(a - 1, b));
}
int Lib::div(int a, int b) {
	if ((a == 0) || (b == 0)) return 0;
	if (b == 1) return a;
	if (a == b) return 1;

	if (b < 0) return -div(a, -b);
	if (a < 0) return div(-a, b);

	return add(1 ,div(sub(a, b), b));
}
int Lib::mod(int a, int b) {
	if ((a == 0) || (b == 0)) return 0;

	if (a < b) return a;

	return mod(sub(a,b) , b);
}
int Lib::StrlenRec(const char* str) {
	if (!*str) return 0;
	return 1 + StrlenRec(str + 1);
}
void Lib::StrcpyRec(char* dest, const char* src) {
	if (!*src) return;

	*dest = *src;
	StrcpyRec(dest + 1, src + 1);
};

void Lib::StrncpyRec(char* dest, const char* src, int size) {
	if (!*src) return;
	if (size == 0) return;
	*dest = *src;
	StrncpyRec(dest + 1, src + 1, size - 1);
}
void Lib::ZeroMemory(char* dest, int size) {
	if (size <= 0) return;
	dest = 0;
	ZeroMemory(dest + 1, size - 1);
}
int Lib::StrCmp(const char* str1, const char* str2) {
	if (!*str1 && !*str2) return 0;
	if (!str1) return -1;
	if (!str2) return 1;
	if (*str1 < *str2) return -1;
	if (*str1 > *str2) return 1;
	return StrCmp(str1 + 1, str2 + 1);
}
int Lib::mulTerminalRecursion(int a, int b, int res = 0) {
	if ((a == 0) || (b == 0)) return res;
	if (a == 1) return res + a;
	if (a == 1) return res + b;
	if (b > 0) return mulTerminalRecursion(a, b - 1, res + a);
	else return mulTerminalRecursion(a, -b, -res);
}

int Lib::divTerminalRecursion(int a, int b, int res) {
	if (b == 0) return res;
	if (a == 0) return res;
	if (b == 1) return res + a;

	if (b < 0) return -divTerminalRecursion(a, -b, -res);
	if (a < 0) return divTerminalRecursion(-a, b, -res);

	if (a < b) return res;

	return divTerminalRecursion(a-b, b, res + 1);
};