#include "alu.h"
#include <floatieee.h>

alu::alu(){

}

std::vector<int> alu::obtenerSignificativo(int exponente, floatIEEE *operando){
    std::vector<int> significativo;
    significativo.push_back(1);
    for(int i = 0; i < exponente; i++){
        significativo.push_back(operando->getMantisa().at(i));
    }
}

int alu::verExponente(floatIEEE *operando1, floatIEEE *operando2){
    int exponenteParaOperar = 0;
    if(operando1->exponenteADecimal() > operando2->exponenteADecimal()){
        exponenteParaOperar = operando1->exponenteADecimal() - operando2->exponenteADecimal();
    }else{
        exponenteParaOperar = operando2->exponenteADecimal() - operando1->exponenteADecimal();
    }
    return exponenteParaOperar;
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
