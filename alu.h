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
        floatIEEE producto(floatIEEE* operando1, floatIEEE* operando2);
        floatIEEE suma(floatIEEE* operando1, floatIEEE* operando2);
        floatIEEE division(floatIEEE *operando1, floatIEEE *operando2);
        std::vector<int> sumar(std::vector<int> sumando1,  std::vector<int> sumando2);
        std::vector<int> restar(std::vector<int> minuendo,  std::vector<int> sustraendo);
};

#endif // ALU_H
