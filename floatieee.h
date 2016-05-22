#ifndef FLOATIEEE_H
#define FLOATIEEE_H

#include <vector>
#include <string>
#include <bitset>
#include <string.h>
#include <QString>

class floatIEEE
{
    public:
        floatIEEE();
        floatIEEE(float numero);
        floatIEEE(std::vector<int> numero);
        QString getHexadecimal();
        std::vector<int> getFloatingPoint( float value, std::string* cadena);
        float getDecimal();
        std::string aCadena();
        int exponenteADecimal();
        std::vector<int> getMantisa();
        float getNumero();
        int getSigno();
        void setSigno(int signo);
        void setExponente(std::vector<int> exponente);
        void setExponente(int exponenteDecimal);
        void setMantisa(std::vector<int> mantisa);
        void procesarNumero();      //con el signo, exponente y mantisa ya introducidos, calcula el resto de atributos

    private:
        int signo;
        float numero;
        std::vector<int> exponente;
        std::vector<int> mantisa;
        std::vector<int> numeroPasado;      //vector con el float entero en IEEE 754
        std::string cadenaNumeroPasado;
};

#endif // FLOATIEEE_H
