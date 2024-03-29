#ifndef ALU_H
#define ALU_H

#include <vector>
#include <floatieee.h>


class alu
{
    public:
        alu();
        std::vector<int> obtenerSignificativo(int exponente, floatIEEE *operando);
        //le pasamos el resultado como puntero para guardarlo directamente
        int verExponente(floatIEEE *operando1, floatIEEE *operando2);
        floatIEEE producto(floatIEEE* factor1, floatIEEE* factor2);
        floatIEEE suma(floatIEEE* operando1, floatIEEE* operando2);
        floatIEEE division(floatIEEE* dividendo, floatIEEE* divisor);
        std::vector<int> sumar(std::vector<int> sumando1,  std::vector<int> sumando2, bool sumaMantisas);
        std::vector<int> restar(std::vector<int> minuendo,  std::vector<int> sustraendo, bool restaMantisas);
};

#endif // ALU_H
