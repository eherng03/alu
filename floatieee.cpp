#include "floatieee.h"
#include <string>
#include <string.h>
#include <sstream>
#include <vector>
#include <bitset>
#include <math.h>
#include <ostream>

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




std::string floatIEEE::getHexadecimal()
{
   std::string hexadecimal;
   hexadecimal.append("0x");
   std::string bitsParaPasar;
   for(int i = 0; i < 32; i){
       bitsParaPasar.clear();
       for(int j = 0; j < 4; j++){
           std::ostringstream temp;  //temp as in temporary
           temp << numeroPasado.at(i);
           bitsParaPasar.append(temp.str());
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

// Convert the 32-bit binary into the decimal
float floatIEEE::getDecimal(){
//    std::string HexNumber = getHexadecimal();


//    bool negative  = !!(HexNumber & 0x80000000);
//    int  exponent  =   (HexNumber & 0x7f800000) >> 23;
//    int sign = negative ? -1 : 1;

//    Subtract 127 from the exponent
//    exponent -= 127;

//    //Convert the mantissa into decimal using the
//    last 23 bits
//    int power = -1;
//    float total = 0.0;
//    for ( int i = 0; i < 23; i++ )
//    {
//        int c = cadenaNumeroPasado[ i + 9 ] - '0';
//        total += (float) c * (float) pow( 2.0, power );
//        power--;
//    }
//    total += 1.0;

//    float value = sign * (float) pow( 2.0, exponent ) * total;

    return NULL;   //return value;
}

std::vector<int> floatIEEE::getMantisa(){
    return mantisa;
}

int floatIEEE::exponenteADecimal(){
    int result = 0;
    for(int i = 0; i < exponente.size(); i++){
        result = result + pow(2, i)*exponente.at(i);
    }
    return result;
}

std::string floatIEEE::aCadena(){
    return cadenaNumeroPasado;
}
