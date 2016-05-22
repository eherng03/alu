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

floatIEEE alu::producto(floatIEEE* factor1, floatIEEE* factor2){
    floatIEEE resultado;
    int exponenteResultado;
    exponenteResultado = factor1->exponenteADecimal() + factor2->exponenteADecimal();
    resultado.setExponente(exponenteResultado);
    if(factor1->getSigno() != factor2->getSigno()){
        resultado.setSigno(1);
    }else{
        resultado.setSigno(0);
    }
}

floatIEEE alu::division(floatIEEE* dividendo, floatIEEE* divisor){
    floatIEEE resultado;
    std::vector<int> mantisaDividendo;
    std::vector<int> mantisaDivisor;
    std::vector<int> mantisaResultado;
    std::vector<int> mantisaDividendoAux;
    std::vector<int> mantisaDivisorAux;

    //el signo es negativo si los signos son diferentes
    if(dividendo->getSigno() != divisor->getSigno()){
        resultado.setSigno(1);
    }else{ //el signo es positivo si los signos son iguales
        resultado.setSigno(0);
    }
    //le pongo el 1 que omite la mantisa para operar con ello
    mantisaDividendo.push_back(1);
    mantisaDivisor.push_back(1);
    for(int i = dividendo->getMantisa().size() - 1; i >= 0; i--){
        mantisaDividendo.push_back(dividendo->getMantisa().at(i));
        mantisaDivisor.push_back(divisor->getMantisa().at(i));
    }

    /*Repito 23 veces el siguiente algoritmo:
     *        -Si se puede resto el divisor del dividendo y lo almaceno en el dividendo
     *        (teniendo en cuenta que la resta no me devuelve el primer 1 y lo tengo
     *         que añadir) y meto un uno en la mantisa resultado.
     *        -Si no puedo restar le meto un cero a la mantisa resultado.
     *        -Desplazo el divisor una posición a la derecha
     */

    for(int j = 0; j < 23; j++){
        mantisaDividendoAux.clear();
        mantisaDivisorAux.clear();
        if(mantisaDividendo >= mantisaDivisor){
            int desplazamiento = verExponente(dividendo, divisor);
            //Obtenemos la parte significativa desplazando las mantisas
            if(abs(dividendo->getNumero()) < abs(divisor->getNumero())){
                mantisaDividendo = obtenerSignificativo(desplazamiento, dividendo);
                mantisaDivisor = obtenerSignificativo(0, divisor);
            }else{
                mantisaDivisor = obtenerSignificativo(desplazamiento, divisor);
                mantisaDividendo = obtenerSignificativo(0, dividendo);
            }
           mantisaDividendoAux = restar(mantisaDividendo, mantisaDivisor);
           mantisaDividendo.clear();
           mantisaDividendo.push_back(1);
           for(int x = 0; x < mantisaDividendoAux.size(); x++){
               mantisaDividendo.push_back(mantisaDividendoAux.at(x));
           }
           mantisaResultado.push_back(1);
        }else{
           mantisaResultado.push_back(0);
        }
        mantisaDivisorAux.push_back(0);
        for(int y = 0; y < mantisaDivisor.size() - 2; y++){
            mantisaDivisorAux.push_back(mantisaDivisor.at(y));
        }
        mantisaDivisor = mantisaDivisorAux;
    }
    //le doy la vuelta a la mantisaResultado para guardarla bien en el atributo de resultado
    for(int k = mantisaResultado.size() - 1; k >= 0; k--){
        resultado.getMantisa().push_back(mantisaResultado.at(k));
    }
    resultado.procesarNumero();

    return resultado;
}



floatIEEE alu::suma(floatIEEE* operando1, floatIEEE* operando2){
    floatIEEE resultado;
    std::vector<int> mantisaResultado;
    int desplazamiento = verExponente(operando1, operando2);
    int exponenteDecimal = 0;
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

     //si tienen signo diferente se resta del mayor en valor absoluto el menor
    }else{
        if(abs(operando1->getNumero()) < abs(operando2->getNumero())){
            mantisaResultado = restar(operando2ParaOperar, operando1ParaOperar);
            resultado.setSigno(operando2->getSigno());
        }else{
            mantisaResultado = restar(operando1ParaOperar, operando2ParaOperar);
            resultado.setSigno(operando1->getSigno());
        }
    }

    //comprobamos la dimensión de la mantisa, si es diferente de 23 habrá que cambiar el exponente
    if(mantisaResultado.size() != 23){
        if(operando1->exponenteADecimal() > operando2->exponenteADecimal()){
            exponenteDecimal = operando1->exponenteADecimal() + (mantisaResultado.size() - 23);

        }else{
            exponenteDecimal = operando2->exponenteADecimal() + (mantisaResultado.size() - 23);
        }
    }

    resultado.setExponente(exponenteDecimal);

    //Procesamos la mantisa
    if(mantisaResultado.size() > 23){
        while(mantisaResultado.size() > 23){
            mantisaResultado.pop_back();
        }
    }else if(mantisaResultado.size() < 23){
        while(mantisaResultado.size() < 23){
            mantisaResultado.push_back(0);
        }
    }
    resultado.setMantisa(mantisaResultado);

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
    if(carry == 1){
        resultadoAux.push_back(carry);
    }

    for(j = resultadoAux.size() - 2; j >= 0; j--){       //Para darle la vuelta al resultado
        resultado.push_back(resultadoAux.at(j));
    }
    return resultado;
}


std::vector<int> alu::restar(std::vector<int> minuendo,  std::vector<int> sustraendo){
    int carry = 0;
    int i;
    int j;
    int x;
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

    //como al principio puede haber ceros, en x guardamos el indice del primer uno
    x = resultadoAux.size() - 1;
    while(resultadoAux.at(x) == 0){
          x--;
    }

    //empieza en x - 1, obviando el primer uno del resultado para que nos de la mantisa (aunque puede tener menor dimension que 23, lo miramos luego)
    for(j = x - 1; j >= 0; j--){      //Para darle la vuelta al resultado
            resultado.push_back(resultadoAux.at(j));
    }


    return resultado;
}


