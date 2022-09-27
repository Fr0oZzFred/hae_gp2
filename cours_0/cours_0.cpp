// cours_0.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <string>
#include <cstdint>
#include <unordered_map>

using namespace std;

int main()
{
	//std::cout << "Hello World!\n";
	printf("12345\n");
	printf("0\n \n");

	std::string zero = "0";
	char zeroC[] = "0";
	std::cout << zeroC << " c++ style \n";
	printf("%s c style\n", zeroC);
	printf("%0.1lf \n", 0.6666666f);
	printf("%f \n", 0.666666f);
	printf("%f \n \n", 0.66666666f);


	float half = 0.5f;
	printf("%f c style\n", half);
	std::cout << std::to_string(half) << " c++ style\n\n";


	printf("toto\n\n");


	int val = 123456789123456789; // Supérieur à 32 Bits
	printf("%i c style\n", val);
	std::cout << std::to_string(val) << " c++ style\n\n";

	std::uint64_t int64 = 123456789123456789;
	printf("%lld c style\n", int64);
	cout << std::to_string(int64) << " c++ style\n";
	cout << int64 << " c++ style\n\n";


	cout << "12345" << endl;
	cout << "12345\n";
	cout << to_string(12345) << "\n\n";


	struct Toto {
		float x = 0.777f;
	};

	Toto toto;
	cout << to_string(toto.x) << "\n";

	struct {
		float x = 0.777f;
	}tutu;

	cout << to_string(tutu.x) << "\n\n";

	{
		std::unordered_map<int, std::string> t;
		t[0] = "toto";
		t[1] = "tutu";
		t[2] = "tata";
		cout << t[0] << "\n";
		for (auto iter = t.begin(); iter != t.end(); iter++)
		{
			auto& p = *iter;
			cout << p.first << " = " << p.second << "\n";
		}

		printf("\n");

		for (auto& p : t) {
			cout << p.first << " = " << p.second << "\n";
		}

		printf("\n");


		for (std::unordered_map<int, std::string>::iterator iter = t.begin(); iter != t.end(); iter++)
		{
			auto& p = *iter;
			cout << p.first << " = " << p.second << "\n";
		}

		printf("\n");

		for (std::pair<const int, std::string>& p : t) {
			cout << p.first << " = " << p.second << "\n";
		}

		printf("\n");

	}

	{
		int c = 0;
		int tab[] = { 0, 1, 2, 3, 4 };
		int* d = &tab[0];
		d++;
		*d = 666;
		int* e0 = nullptr;
		int* e1 = NULL;
		int* e2 = 0;
		int here = 0;
	}
	{
		int c = 0;
		int& d = c;
		d++;
		int here;
	}

	vector<std::string> p;
	for (size_t i = 0; i < 100000; i++)
	{
		p.push_back(to_string(i));
	}

	int here = 0; // Voir perf
	{
		for (size_t i = 0; i < 100000; i++)
		{
			std::string& pelem = p[i];
		}
		int here = 0; // Voir perf
	}

	int* x, y; //Adresse puis var

	int tab[] = { 66, 1, 2 ,3 };
	int* c = &tab[0];
	//Point d'arrêt
	*c = -1;
	*c++;
	(*c)++;
	*++c;
	++*c;
}
/*template<int>
class Type {
	int tutu;
};

	class B : Foo {

	};

	struct Foo {
		float x;
	};

	struct A : Foo {
		float y;
	};*/

