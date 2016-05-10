#ifndef FLOATIEEE_H
#define FLOATIEEE_H

#include <vector>

class floatIEEE
{
public:
    floatIEEE(float numero);
    std::vector<int> getFloatingPoint( float value, std::string* cadena);

private:
    int signo;
    float numero;
    std::vector<int> exponente;
    std::vector<int> mantisa;
    std::vector<int> numeroPasado;
};

#endif // FLOATIEEE_H
