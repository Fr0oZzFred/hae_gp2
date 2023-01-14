#pragma once

#include <chrono>
#include <ctime>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"


class Lib{
public:
	static void Memcpy(char* dest, const char* src, int size) {
		for(int i = 0; i < size;++i)
			dest[i] = src[i];
	};

	//renvoie nullptr si le char c n'est pas trouvé
	//sinon renvoie le ptr vers la u est le character
	static const char* StrChr(const char* src, char c) {
		while (*src && (*src != c))
			src++;
		if (!*src)
			return nullptr;
		return src;
	};

	static bool StrPrefix( const char* src, const char*tok){
		int i = 0;
		while (tok[i]) {
			if (tok[i] != src[i])
				return false;
			else 
				i++;
		}
		return true;
	}

	//sapin
	//pin
	static const char* StrStr(const char * src, const char * tok){
		while (*src && !StrPrefix(src, tok)) 
			src++;
		if (!*src)
			return nullptr;
		return src;
	};


	// P(0) => P(1)
	// P(N) => P(N+1)
	// combine ces deux vérité => l'algo est correcte
	static void MemcpyRec(char* dest, char* src, int size) {
		//cas initial ( p(0) => p(1) )
		if (size <= 0)
			return;
		//cas recurrent ( p(n) => pn+1)
		*dest = *src;
		MemcpyRec(dest + 1, src + 1, size - 1);
		//combine
		;
		//on retourne
		return;
	};


	static const char* StrChrRec(const char* src, char c) {
		//cas initial ( p(0) => p(1) )
		if (!*src)
			return nullptr;
		//on a resolu ( un des cas initiaux )
		if (*src == c)
			return src;
		//cas recurrent  p(n) => pn+1
		return //combine
			StrChrRec(src + 1, c);
	};

	static bool StrPrefixRec(const char* src, const char* c){
		if (src == nullptr) return false;
		if (*c == 0 ) return true;
		if(*src != *c )
			return false;
		return StrPrefixRec(src+1,c+1);
	}

	static const char* StrStrRec(const char* src, const char* prefix) {
		//y a peut etre une sous fonction a se créer pour se simplifier la vie
		//cas initial ( p(0) => p(1) )
		if (src == nullptr) return nullptr;
		if (*src == 0) {
			if (*src == *prefix)
				return src;
			return nullptr;
		}
		if (StrPrefixRec(src, prefix))
			return src;
		//cas recurrent  p(n) => pn+1
		//combine
		return  StrStrRec(src + 1, prefix);
	}

	static int add(int a, int b) {
		//0 1 - +1, d'autres fonctions qui marchent deja, appel recursif
		if (b == 0) return a;
		if (a == 0) return b;
		if( b < 0 )
			return add(a - 1, b + 1);
		return add(a + 1, b - 1);
	};

	static int add2(int a, int b) {
		//0 1 - +1, d'autres fonctions qui marchent deja, appel recursif
		if (b == 0) return a;
		if (a == 0) return b;
		if (b < 0)
			return add(a - 1, b + 1);
		return 1 + add(a, b - 1);
	};


	static void StrCpy(char * dst,const char *src) {
		if (!src) return;
		if (!*src) {
			*dst = 0;
			return;
		}
		else {
			*dst = *src;
			return StrCpy(dst + 1, src + 1);
		}
	}; 
	
	static void StrNCpy(char* dst, const char* src, int charMaxToCopy ) {
		if (!src) return;
		if (charMaxToCopy <= 0)
			return;
		if (!*src) {
			*dst = 0;
			return;
		}
		else {
			*dst = *src;
			return StrNCpy(dst + 1, src + 1, charMaxToCopy-1);
		}
	};

	static int sub(int a, int b) {
		return add(a , - b);
	};

	static int mul(int a, int b) {
		if (a == 0 || b == 0) return 0;
		if (a == 1 ) return b;
		if (b == 1 ) return a;
		if (b > 0)
			return add(a , mul(a, b - 1)); 
		else
			return - mul(a, -b);
	};

	// [0] -> stack ( appels de fonction et les variables locales .......................................................... heaps alloc dynamique, variables globales // 
	static int mulTerminalRecursion(int a, int b, int res = 0) {
		if (a == 0 || b == 0) return res;
		if (a == 1) return b + res;
		if (b == 1) return a + res;
		if (b > 0){
			//?
			return mulTerminalRecursion(a, b - 1, a + res);
		}
		else {
			//?
			return mulTerminalRecursion(a, -b, -res);
		}
	}

	static int divTR(int a, int b, int res = 0) {
		if (a == 0) return res;
		if (b == 0) {
#ifdef _DEBUG
			throw "assert";
#endif
			return res;
		}
		if (b == 1) return a + res;
		if (b < 0)
			return divTR(a, -b,-res);
		if (a < 0)
			return divTR(-a, b,-res);
		if (a < b)	return 0 + res;
		if (a == b)	return 1 + res;

		int leftover = sub(a, b);
		return divTR(leftover, b, 1 + res);//?
	}

	static int div(int a, int b) {
		if (a == 0) return 0;
		if (b == 0) {
#ifdef _DEBUG
			throw "assert";
#endif
			return 0;
		}
		if (b == 1) return a;
		if (b < 0)
			return -div(a, -b);
		if (a < 0)
			return -div(-a, b);
		if( a < b )	return 0;
		if (a == b)	return 1;
		return 1+div(sub(a, b), b);
	};

	static int StrLenRec(const char* str) {
		//retourn la longeur de str en recursif
		if (!str)return 0;
		if (!*str)return 0;
		return 1 + StrLenRec(str + 1);
	};

	static void ZeroMemoryRec(char* mem, int nbBytes) {
		if (!mem) return;
		if (nbBytes <= 0) return;
		*mem = 0;
		ZeroMemoryRec(mem + 1, nbBytes - 1);
	};

	static int StrCmp( const char * a, const char * b){
		//faire les cas initiaux
		if(!*a && !*b) return 0;
		if (!a) return -1;
		if (!b) return 1;
		//a ...
		//b ...
		if (*a < *b) return -1;
		if (*a > *b) return 1;
		return StrCmp(a + 1, b + 1);
	}

	static int rand();

	// 0 - 1 
	//=> *2 
	//0 - 2 
	// -1
	// -1 1
	static float randF();

	static float lerp(float a, float b, float t) {
		return a + (b - a) * t;
	};

	static sf::Vector2f lerp(sf::Vector2f a, sf::Vector2f b, float t) {
		sf::Vector2f diff = b - a;
		diff.x *= t;
		diff.y *= t;
		return a + diff;
	};
	static sf::Color lerp(sf::Color a, sf::Color b, float t) {
		return sf::Color(
			a.r + (b.r - a.r) * t,
			a.g + (b.g - a.g) * t,
			a.b + (b.b - a.b) * t,
			a.a + (b.a - a.a) * t
		);
	};

	static double getTimestamp() {
		std::chrono::nanoseconds ns =
			std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch());
		return ns.count() / 1000000000.0;
	};


	static bool safeNormalize(sf::Vector2f & inOut ) {
		float distSq = inOut.x * inOut.x + inOut.y * inOut.y;
		if( distSq ){
			float dist = sqrtf(distSq);
			inOut.x /= dist;
			inOut.y /= dist;
			return true;
		}
		return false;
	};
	static sf::Vector2f normalize(sf::Vector2f& inOut) {
		float distSq = inOut.x * inOut.x + inOut.y * inOut.y;
		if (distSq) {
			float dist = sqrtf(distSq);
			inOut.x /= dist;
			inOut.y /= dist;
			return inOut;
		}
		return sf::Vector2f(0, 0);
	};

	static float lookAt(sf::Vector2f start, sf::Vector2f end) {
		sf::Vector2f dir = end - start;
		Lib::safeNormalize(dir);
		float angle = std::atan2(dir.y, dir.x);
		angle *= 180.0f / 3.14159f;
		return angle;
	};
	auto getAngle(float a) {
		return sf::Vector2f(
			std::cos(a),
			std::sin(a)
		);
	};
};

#define SFML_ORANGE sf::Color(0xFC5C49ff)