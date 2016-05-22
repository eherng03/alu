#include "floatieee.h"
#include <string>
#include <string.h>
#include <sstream>
#include <vector>
#include <bitset>
#include <math.h>
#include <ostream>
#include <QString>

floatIEEE::floatIEEE(){

}

floatIEEE::floatIEEE(float numero){
    this->numero = numero;
    numeroPasado = getFloatingPoint(numero, &cadenaNumeroPasado);
    signo = numeroPasado.at(0);
    for (int i = 1; i < 9; i++){
       exponente.push_back(numeroPasado.at(i));
    }
    for(int j = 9; j < 32; j++){
        mantisa.push_back(numeroPasado.at(j));
    }
}

floatIEEE::floatIEEE(std::vector<int> numero){
    for(int i = 0; i < 32; i++){
        cadenaNumeroPasado.at(i) = numero.at(i);
    }
    numeroPasado = numero;
    this->numero = getDecimal();
    signo = numeroPasado.at(0);
    for (int i = 1; i < 9; i++){
       exponente.push_back(numeroPasado.at(i));
    }
    for(int j = 9; j < 32; j++){
        mantisa.push_back(numeroPasado.at(j));
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

float floatIEEE::getNumero(){
    return numero;
}




QString floatIEEE::getHexadecimal()
{
   QString hexadecimal;
   hexadecimal.append("0x");
   QString bitsParaPasar;
   for(int i = 0; i < 32; i){
       bitsParaPasar.clear();
       for(int j = 0; j < 4; j++){
           std::ostringstream temp;  //temp as in temporary
           temp << numeroPasado.at(i);
           bitsParaPasar.append(QString::fromStdString(temp.str()));
           i++;
       }


       if(bitsParaPasar.compare("0000") == 0){
           hexadecimal.append("0");
       }else if(bitsParaPasar.compare("0001") == 0){
           hexadecimal.append("1");
       }else if(bitsParaPasar.compare("0010") == 0){
           hexadecimal.append("2");
       }else if(bitsParaPasar.compare("0011") == 0){
           hexadecimal.append("3");
       }else if(bitsParaPasar.compare("0100") == 0){
           hexadecimal.append("4");
       }else if(bitsParaPasar.compare("0101") == 0){
           hexadecimal.append("5");
       }else if(bitsParaPasar.compare("0110") == 0){
           hexadecimal.append("6");
       }else if(bitsParaPasar.compare("0111") == 0){
           hexadecimal.append("7");
       }else if(bitsParaPasar.compare("1000") == 0){
           hexadecimal.append("8");
       }else if(bitsParaPasar.compare("1001") == 0){
           hexadecimal.append("9");
       }else if(bitsParaPasar.compare("1010") == 0){
           hexadecimal.append("A");
       }else if(bitsParaPasar.compare("1011") == 0){
           hexadecimal.append("B");
       }else if(bitsParaPasar.compare("1100") == 0){
           hexadecimal.append("C");
       }else if(bitsParaPasar.compare("1101") == 0){
           hexadecimal.append("D");
       }else if(bitsParaPasar.compare("1110") == 0){
           hexadecimal.append("E");
       }else if(bitsParaPasar.compare("1111") == 0){
           hexadecimal.append("F");
       }
   }
   return hexadecimal;
}

//Método que pasa el float en IEEE entero a su equivalente en float, y ala vez lo amacena en su atributo
float floatIEEE::getDecimal(){
    float mantisaFloat = 0;
    float resultado = 0;

    for(int i = 1; i < mantisa.size(); i++){
        mantisaFloat = mantisaFloat + (mantisa.at(i-1)*(1/(pow(2, i))));
    }

    resultado = pow(-1, signo) * ((1 + mantisaFloat) * pow(2, exponenteADecimal()));
    numero = resultado;
    return resultado;
}

std::vector<int> floatIEEE::getMantisa(){
    return mantisa;
}

int floatIEEE::exponenteADecimal(){
    int result = 0;
    int j = 7;
    for(int i = 0; i < exponente.size(); i++){
        result = result + pow(2, i)*exponente.at(j);
        j--;
    }
    return result - 127;
}

std::string floatIEEE::aCadena(){
    return cadenaNumeroPasado;
}

int floatIEEE::getSigno(){
    return signo;
}

void floatIEEE::setSigno(int signo){
    this->signo = signo;
}

void floatIEEE::setExponente(std::vector<int> exponente){
    this->exponente = exponente;
}

void floatIEEE::setExponente(int exponenteDecimal){
    std::vector<int> exponenteAux;
    int numeroCerosAnadir = 0;
    exponenteDecimal = exponenteDecimal + 127;
    while(exponenteDecimal > 1){
        exponenteAux.push_back(exponenteDecimal % 2);
        exponenteDecimal = exponenteDecimal / 2;
    }
    exponenteAux.push_back(1);
    if(exponenteAux.size() < 8){
        numeroCerosAnadir = 8 - exponenteAux.size();
    }
    for(int i = 0; i < numeroCerosAnadir; i++){
        exponenteAux.push_back(0);
    }

    //Lo invertimos:
    for(int j = exponenteAux.size() - 1; j >= 0; j--){
        exponente.push_back(exponenteAux.at(j));
    }
}

void floatIEEE::setMantisa(std::vector<int> mantisa){
    this->mantisa = mantisa;
}

void floatIEEE::procesarNumero(){
    numeroPasado.push_back(signo);
    for(int x = 0; x < exponente.size(); x++){
        numeroPasado.push_back(exponente.at(x));
    }
    for(int y = 0; y < mantisa.size(); y++){
        numeroPasado.push_back(mantisa.at(y));
    }

    for(int i = 0; i < this->numeroPasado.size(); i++){
        if(this->numeroPasado.at(i) == 0){
            this->cadenaNumeroPasado.append("0");
        }else if(this->numeroPasado.at(i) == 1){
            this->cadenaNumeroPasado.append("1");
        }
    }

    this->numero = this->getDecimal();

}


