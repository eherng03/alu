#include "alu.h"
#include <floatieee.h>
#include <stdlib.h>
#include <vector>

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
   // floatIEEE resultado = new floatIEEE();

}

floatIEEE alu::suma(floatIEEE* operando1, floatIEEE* operando2){
    floatIEEE resultado;
    std::vector<int> mantisaResultado;
    int desplazamiento = verExponente(operando1, operando2);
    std::vector<int> operando1ParaOperar;
    std::vector<int> operando2ParaOperar;

    //Obtenemos la parte significativa desplazando las mantisas
    if(abs(operando1->getNumero()) < abs(operando2->getNumero())){
        operando1ParaOperar = obtenerSignificativo(desplazamiento, operando1);
        operando2ParaOperar = obtenerSignificativo(0, operando2);
    }else{
        operando2ParaOperar = obtenerSignificativo(desplazamiento, operando2);
        operando1ParaOperar = obtenerSignificativo(0, operando1);
    }

    //si los dos tienen el mismo signo se suman
    if(operando1->getSigno() == operando2->getSigno()){
        mantisaResultado = sumar(operando1ParaOperar, operando2ParaOperar);
        resultado.setSigno(operando1->getSigno());

        //tener en cuenta que debido al acarreo la mantisa nueva puede tener 25 bits, meter solo los 24 primeros
        //exponente

     //si tienen signo diferente se resta del mayor en valor absoluto el menor
    }else{
        if(abs(operando1->getNumero()) < abs(operando2->getNumero())){
            mantisaResultado = restar(operando2ParaOperar, operando1ParaOperar);
            resultado.setSigno(operando2->getSigno());
            resultado.setMantisa(mantisaResultado);
            //exponente del mayor?
        }else{
            mantisaResultado = restar(operando1ParaOperar, operando2ParaOperar);
            resultado.setSigno(operando1->getSigno());
            resultado.setMantisa(mantisaResultado);
            //exponente del mayor?
        }
    }


    //Meter todo al floatieee resultado
    resultado.procesarNumero();
    return resultado;
}

std::vector<int> alu::sumar(std::vector<int> sumando1,  std::vector<int> sumando2){
    int carry = 0;
    int i;
    int j;
    std::vector<int> resultadoAux;
    std::vector<int> resultado;
    for(i = sumando1.size() - 1 ; i >= 0; i--){
        if(sumando1.at(i) + sumando2.at(i) + carry == 0){
           resultadoAux.push_back(0);
            carry = 0;
        }else if(sumando1.at(i) + sumando2.at(i) + carry == 1){
            resultadoAux.push_back(1);
            carry = 0;
        }else if(sumando1.at(i) + sumando2.at(i) + carry == 2){
            resultadoAux.push_back(0);
            carry = 1;
        }else if(sumando1.at(i) + sumando2.at(i) + carry > 2){
            resultadoAux.push_back(1);
            carry = 1;
        }
    }
    resultadoAux.push_back(carry);

    for(j = resultadoAux.size() - 1; j >= 0; j--){       //Para darle la vuelta al resultado
        resultado.push_back(resultadoAux.at(j));
    }
    return resultado;
}


std::vector<int> alu::restar(std::vector<int> minuendo,  std::vector<int> sustraendo){
    int carry = 0;
    int i;
    int j;
    std::vector<int> resultadoAux;
    std::vector<int> resultado;
    for(i = minuendo.size() - 1; i >= 0; i--){
        if(minuendo.at(i) == 0 && sustraendo.at(i) == 0 && carry == 0){
           resultadoAux.push_back(0);
           carry = 0;
        }else if(minuendo.at(i) == 0 && sustraendo.at(i) == 0 && carry == 1){
            resultadoAux.push_back(1);
            carry = 1;
        }else if(minuendo.at(i) == 0 && sustraendo.at(i) == 1 && carry == 0){
            resultadoAux.push_back(1);
            carry = 1;
        }else if(minuendo.at(i) == 0 && sustraendo.at(i) == 1 && carry == 1){
            resultadoAux.push_back(0);
            carry = 0;
        }else if(minuendo.at(i) == 1 && sustraendo.at(i) == 0 && carry == 0){
            resultadoAux.push_back(1);
            carry = 0;
        }else if(minuendo.at(i) == 1 && sustraendo.at(i) == 0 && carry == 1){
            resultadoAux.push_back(0);
            carry = 0;
        }else if(minuendo.at(i) == 1 && sustraendo.at(i) == 1 && carry == 0){
            resultadoAux.push_back(0);
            carry = 0;
        }else if(minuendo.at(i) == 1 && sustraendo.at(i) == 1 && carry == 1){
            resultadoAux.push_back(1);
            carry = 0;
        }
    }

    for(j = resultadoAux.size() - 1; j >= 0; j--){       //Para darle la vuelta al resultado
        resultado.push_back(resultadoAux.at(j));
    }
    return resultado;
}

floatIEEE alu::division(floatIEEE* operando1, floatIEEE* operando2){

}
