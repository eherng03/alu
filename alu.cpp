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
    int iteraciones;
    int numeroAMultiplicar = 0;
    std::vector<int> multiplicando;
    std::vector<int> multiplicador;
    std::vector<int> vectorSumaAnterior;            //La suma en cada iteraccion, del actual con los anteriores sumados
    std::vector<int> multiplicacionParcial;
    std::vector<int> mantisaFinal;
    exponenteResultado = factor1->exponenteADecimal() + factor2->exponenteADecimal();

    //Insertamos el primer uno que no tiene la mantisa en el float
    multiplicando.push_back(1);
    multiplicador.push_back(1);
    std::vector<int> mantisa1 = factor1->getMantisa();
    multiplicando.insert(multiplicando.end(), mantisa1.begin(), mantisa1.end() );
    std::vector<int> mantisa2 = factor2->getMantisa();
    multiplicador.insert(multiplicador.end(), mantisa2.begin(), mantisa2.end() );

    if(factor1->getSigno() != factor2->getSigno()){
        resultado.setSigno(1);
    }else{
        resultado.setSigno(0);
    }

    //Necesitamos tantas iteracciones como bits tiene el multiplicador
    iteraciones = multiplicador.size() - 1;
    //El primer vector auxiliar1 es la primera multiplicacion, los siguientes son la suma de los dos anteriores
    vectorSumaAnterior.push_back(0);        //Añado un 0 para poder sumarlo mas tarde
    numeroAMultiplicar = multiplicador.at(iteraciones);
    for(int i = 0; i < multiplicando.size() ; i++){     //recorre los elementos del multiplicando
        vectorSumaAnterior.push_back(multiplicando.at(i) * numeroAMultiplicar);
    }
    iteraciones--;
    while(iteraciones >= 0){            //recorre los elementos del multiplicador(el de abajo)
        multiplicacionParcial.clear();
        numeroAMultiplicar = multiplicador.at(iteraciones);
        for(int i = 0; i < multiplicando.size() ; i++){     //recorre los elementos del multiplicando
            multiplicacionParcial.push_back(multiplicando.at(i) * numeroAMultiplicar);
        }
        int sizeMult = multiplicacionParcial.size();
        for(int x = 0; x < vectorSumaAnterior.size() - sizeMult; x++){
            multiplicacionParcial.push_back(0);
        }

        std::vector<int> suma = sumar(vectorSumaAnterior, multiplicacionParcial, true);
        vectorSumaAnterior.clear();
        if(suma.size() == multiplicacionParcial.size()){
            vectorSumaAnterior.push_back(0);
        }
        vectorSumaAnterior.insert(vectorSumaAnterior.end(), suma.begin(), suma.end() );

        iteraciones--;
    }

    int i = 2;
    int posicionFinal = 24;
    if(vectorSumaAnterior.at(0) == 1){
        exponenteResultado++;
        i = 1;
        posicionFinal = 23;
    }

    //VectorAux1 va a ser un vector de 46 elementos, seleccionamos solo los 23 primeros, quitandole el 1
    for(i; i <= posicionFinal; i++){
        mantisaFinal.push_back(vectorSumaAnterior.at(i));
    }


    resultado.setMantisa(mantisaFinal);
    resultado.setExponente(exponenteResultado);
    resultado.procesarNumero();
    return resultado;

}



floatIEEE alu::division(floatIEEE* dividendo, floatIEEE* divisor){
    floatIEEE resultado;
    std::vector<int> mantisaDividendo;
    std::vector<int> mantisaDivisor;
    std::vector<int> mantisaResultado;
    std::vector<int> mantisaDividendoAux;
    std::vector<int> mantisaDivisorAux;
    std::vector<int> mantisaFinal;

    //el signo es negativo si los signos son diferentes
    if(dividendo->getSigno() != divisor->getSigno()){
        resultado.setSigno(1);
    }else{ //el signo es positivo si los signos son iguales
        resultado.setSigno(0);
    }

    int exponente = dividendo->exponenteADecimal() - divisor->exponenteADecimal();

    //le pongo el 1 que omite la mantisa para operar con ello
    mantisaDividendo.push_back(1);
    mantisaDivisor.push_back(1);

    for(int i = 0; i < dividendo->getMantisa().size() - 1; i++){
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

            if(mantisaDividendo == mantisaDivisor){ //Si son iguales la resta da 0
                mantisaDividendo.clear();
                for(int x = 0; x < 23; x++){
                    mantisaDividendo.push_back(0);
                }
            }else{              //si no las restamos
                mantisaDividendoAux = restar(mantisaDividendo, mantisaDivisor, true);
                mantisaDividendo.clear();
                for(int y = 0; y < 23; y++){
                    mantisaDividendo.push_back(mantisaDividendoAux.at(y));
                }
            }

           mantisaResultado.push_back(1);

        }else{
           mantisaResultado.push_back(0);
        }
        //Desplazamos a la derecha la mantisa divisor
        mantisaDivisorAux.push_back(0);
        for(int y = 0; y < 22; y++){
            mantisaDivisorAux.push_back(mantisaDivisor.at(y));
        }
        mantisaDivisor.clear();
        for(int y = 0; y < 23; y++){
            mantisaDivisor.push_back(mantisaDivisorAux.at(y));
        }
    }
    //busco el primer uno
    int primeraPosicionMantisa = 0;
    while(mantisaResultado.at(primeraPosicionMantisa) == 0){
        primeraPosicionMantisa++;
    }

    //calculo el exponente
    exponente = exponente - primeraPosicionMantisa;

    //omito el primer uno
    primeraPosicionMantisa++;

    //calculo la mantisa a partir de omitir el primer uno
    for(int k = primeraPosicionMantisa; k < mantisaResultado.size(); k++){
        mantisaFinal.push_back(mantisaResultado.at(k));
    }
    while(mantisaFinal.size() != 23){
        mantisaFinal.push_back(0);
    }

    //meto todo en el resultado
    resultado.setMantisa(mantisaFinal);
    resultado.setExponente(exponente);

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
        mantisaResultado = sumar(operando1ParaOperar, operando2ParaOperar, false);
        resultado.setSigno(operando1->getSigno());

     //si tienen signo diferente se resta del mayor en valor absoluto el menor
    }else{
        if(abs(operando1->getNumero()) < abs(operando2->getNumero())){
            mantisaResultado = restar(operando2ParaOperar, operando1ParaOperar, false);
            resultado.setSigno(operando2->getSigno());
        }else if(abs(operando1->getNumero()) > abs(operando2->getNumero())){
            mantisaResultado = restar(operando1ParaOperar, operando2ParaOperar, false);
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
    }else{      //Si no tiene el mismo exponente que el mayor
        if(operando1->exponenteADecimal() > operando2->exponenteADecimal()){
            exponenteDecimal = operando1->exponenteADecimal();

        }else{
            exponenteDecimal = operando2->exponenteADecimal();
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

std::vector<int> alu::sumar(std::vector<int> sumando1,  std::vector<int> sumando2, bool sumaMantisas){
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
    if(sumaMantisas){
        j = resultadoAux.size() - 1;    //No le quitamos el primer 1
    }else{
        j = resultadoAux.size() - 2;    //Si
    }

    for(j; j >= 0; j--){       //Para darle la vuelta al resultado
        resultado.push_back(resultadoAux.at(j));
    }
    return resultado;
}


std::vector<int> alu::restar(std::vector<int> minuendo,  std::vector<int> sustraendo, bool restaMantisas){
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
    //Fuera del metodo miramos si ambas son iguales para que la resta nunca de 0 y asi no se salfa de resultadoAux
    x = resultadoAux.size() - 1;
    while(resultadoAux.at(x) == 0){
          x--;
    }

    if(restaMantisas){      //Si restamos las mantisas para la operacion de la dividision no le quitamos el primer uno
        for(j =  resultadoAux.size() - 1; j >= 0; j--){      //Para darle la vuelta al resultado
           resultado.push_back(resultadoAux.at(j));
        }
        while(resultado.size() != 24){
            resultado.push_back(0);
        }
    }else{
        j = x - 1;
        //empieza en x - 1, obviando el primer uno del resultado para que nos de la mantisa (aunque puede tener menor dimension que 23, lo miramos luego)
        for(j; j >= 0; j--){      //Para darle la vuelta al resultado
                resultado.push_back(resultadoAux.at(j));
        }
    }



    return resultado;
}


