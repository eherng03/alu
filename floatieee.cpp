#include "floatieee.h"

floatIEEE::floatIEEE(float numero){
    this->numero = numero;
    std::string cadenaNumeroPasado;
    numeroPasado = getFloatingPoint(numero, cadenaNumeroPasado);
    signo = numeroPasado.at(0);
    for (int i = 1; i < 8; i++){
       exponente.push(numeroPasado.at(i));
    }
    for(int j = 9; j < 32; j++){
        mantisa.push(numeroPasado.at(i));
    }
}

std::vector<int> floatIEEE::getFloatingPoint( float value, std::string* cadena){
    int i;
    std::vector<int> resultado;
    union
    {
         float input;   // assumes sizeof(float) == sizeof(int)
         int   output;
    }    data;

    data.input = value;

    std::bitset<sizeof(float) * CHAR_BIT>   bits(data.output);

    std::string mystring = bits.to_string<char,
                                          std::char_traits<char>,
                                          std::allocator<char> >();
    for(i = 0; i < 32; i++){
        resultado.push_back(mystring.at(i) - 48);
    }

    *cadena = mystring;

    return resultado;
}
