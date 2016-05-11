#include "alu.h"
#include <floatieee.h>

alu::alu(){

}

std::vector<int> alu::obtenerSignificativo(int exponente, floatIEEE *operando){

}

floatIEEE alu::producto(floatIEEE *operando1, floatIEEE *operando2){

}

floatIEEE alu::suma(floatIEEE* operando1, floatIEEE* operando2){

    //DENTRO DE SUMA HAY QUE HACER SUMAR Y RESTAR

//    int carry = 0;
//    //mirar a ver como se introducen los datos en los operadores
//    for(int i = 0; i < 32; i++){
//        if(operando1[i] + operando2[i] + carry == 0){
//            resultado[i] = 0;
//            carry = 0;
//        }else if(operando1[i] + operando2[i] + carry == 1){
//            resultado[i] = 1;
//            carry = 0;
//        }else if(operando1[i] + operando2[i] + carry == 2){
//            resultado[i] = 0;
//            carry = 1;
//        }else if(operando1[i] + operando2[i] + carry > 2){
//            resultado[i] = 1;
//            carry = 1;
//        }
//    }
}

floatIEEE alu::division(floatIEEE* operando1, floatIEEE* operando2){

}
