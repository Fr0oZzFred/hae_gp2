// cours_0.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <string>
#include <cstdint>

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
    std::cout <<  std::to_string(half) << " c++ style\n\n";


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
    
    cout << to_string(tutu.x);
}
