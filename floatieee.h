#ifndef FLOATIEEE_H
#define FLOATIEEE_H

#include <vector>
#include <string>
#include <bitset>

class floatIEEE
{
public:
    floatIEEE();
    floatIEEE(float numero);
    floatIEEE(std::vector<int> numero);
    int getHexadecimal();
    std::vector<int> getFloatingPoint( float value, std::string* cadena);
    float getDecimal();
    std::string aCadena();
    int exponenteADecimal(){
private:
    int signo;
    float numero;
    std::vector<int> exponente;
    std::vector<int> mantisa;
    std::vector<int> numeroPasado;
    std::string cadenaNumeroPasado;
};

#endif // FLOATIEEE_H
