#include "alu.h"
#include <floatieee.h>

alu::alu(){

}

std::vector<int> alu::obtenerSignificativo(int desplazamiento, floatIEEE *operando){
    std::vector<int> significativo;
    for(int i = 0; i < desplazamiento; i++){
        significativo.push_back(0);
    }
    significativo.push_back(1);
    for(int i = 0; i < 23 - desplazamiento; i++){
        significativo.push_back(operando->getMantisa().at(i));
    }
    return significativo;
}

int alu::verExponente(floatIEEE *operando1, floatIEEE *operando2){
    int desplazamiento = 0;
    if(operando1->exponenteADecimal() > operando2->exponenteADecimal()){
        desplazamiento = operando1->exponenteADecimal() - operando2->exponenteADecimal();
    }else{
        desplazamiento = operando2->exponenteADecimal() - operando1->exponenteADecimal();
    }
    return desplazamiento;
}

floatIEEE alu::producto(floatIEEE *operando1, floatIEEE *operando2){

}

floatIEEE alu::suma(floatIEEE* operando1, floatIEEE* operando2){

    int desplazamiento = verExponente(operando1, operando2);
    std::vector<int> operando1ParaOperar;
    std::vector<int> operando2ParaOperar;
    if(operando1->getNumero() < operando2->getNumero()){
        operando1ParaOperar = obtenerSignificativo(desplazamiento, operando1);
        operando2ParaOperar = obtenerSignificativo(0, operando2);
    }else{
        operando2ParaOperar = obtenerSignificativo(desplazamiento, operando2);
        operando1ParaOperar = obtenerSignificativo(0, operando1);
    }

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
