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
};

