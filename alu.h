#ifndef ALU_H
#define ALU_H

#include <vector>


class alu
{
public:
    alu();
    //le pasamos el resultado como puntero para guardarlo directamente
    std::vector<int> producto(std::vector<int> operando1, std::vector<int> operando2);
    std::vector<int> suma(std::vector<int> operando1, std::vector<int> operando2);
    std::vector<int> division(std::vector<int> operando1, std::vector<int> operando2);
};

#endif // ALU_H
