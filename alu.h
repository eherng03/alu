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
    floatIEEE producto(floatIEEE* operando1, floatIEEE* operando2);
    floatIEEE suma(floatIEEE* operando1, floatIEEE* operando2);
    floatIEEE division(floatIEEE *operando1, floatIEEE *operando2);
};

#endif // ALU_H
