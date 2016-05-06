#ifndef FLOATIEEE_H
#define FLOATIEEE_H

#include <vector>

class floatIEEE
{
public:
    floatIEEE(std::vector<int> numero);

private:
    int signo;
    std::vector<int> exponente;
    std::vector<int> significativos;
    std::vector<int> numero;
};

#endif // FLOATIEEE_H
