#pragma once

/*
[][][][][][][][][0] <- fin de la chaîne de caracter
\0 ~= '0'
0
char => int sur 8 bit
*/

int Strlen(const char* str) {
	int idx = 0;
	while (str[idx] != 0)
	{
		idx++;
	}
	return idx;
};

int Strlen2(const char* str) {
	const char* start = str;
	while (*str != 0)
		str++;
	return str - start;
};

int Strlen3(const char* str) {
	const char* start = str;
	while (*str) str++;
	return str - start;
};

int Countc(const char* str, char c) {
	int length = 0;
	int count = 0;
	while (str[length] != 0)
	{
		length++;
		if (str[length] == c) {
			count++;
		}
	}
	return count;
};

void Strcpy(char* dst, const char* src) {
	while (*src)
	{
		*dst = *src;
		src++;
		dst++;
	}
};

void Strncpy(char* dst, const char* src, int nchars) {
	for (int i = 0; i < nchars; i++)
	{
		dst[i] = src[i];
	}
};