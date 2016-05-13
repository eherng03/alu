#ifndef FLOATIEEE_H
#define FLOATIEEE_H

#include <vector>
#include <string>
#include <bitset>
#include <string.h>

class floatIEEE
{
public:
    floatIEEE();
    floatIEEE(float numero);
    floatIEEE(std::vector<int> numero);
    std::string getHexadecimal();
    std::vector<int> getFloatingPoint( float value, std::string* cadena);
    float getDecimal();
    std::string aCadena();
    int exponenteADecimal();
    std::vector<int> getMantisa();
    float getNumero();
private:
    int signo;
    float numero;
    std::vector<int> exponente;
    std::vector<int> mantisa;
    std::vector<int> numeroPasado;      //vector con el float entero en IEEE 754
    std::string cadenaNumeroPasado;
};

#endif // FLOATIEEE_H
