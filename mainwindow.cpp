#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <limits.h>
#include <iostream>
#include <math.h>
#include <bitset>
#include <string>
#include <string.h>
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



// Convert the 32-bit binary encoding into hexadecimal
int MainWindow::binary2Hex( std::string Binary )
{
    std::bitset<32> set(Binary);
    int hex = set.to_ulong();

    return hex;
}

// Convert the 32-bit binary into the decimal
float MainWindow::getFloat32( std::string Binary )
{
    int HexNumber = binary2Hex( Binary );

    bool negative  = !!(HexNumber & 0x80000000);
    int  exponent  =   (HexNumber & 0x7f800000) >> 23;
    int sign = negative ? -1 : 1;

    // Subtract 127 from the exponent
    exponent -= 127;

    // Convert the mantissa into decimal using the
    // last 23 bits
    int power = -1;
    float total = 0.0;
    for ( int i = 0; i < 23; i++ )
    {
        int c = Binary[ i + 9 ] - '0';
        total += (float) c * (float) pow( 2.0, power );
        power--;
    }
    total += 1.0;

    float value = sign * (float) pow( 2.0, exponent ) * total;

    return value;
}

// Get 32-bit IEEE 754 format of the decimal value
std::vector<int> MainWindow::getBinary32( float value, std::string* cadena)
{
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


void MainWindow::on_runButton_clicked()
{
    int i;
    operando1 = ui->operando1->toPlainText().toFloat();
    operando2 = ui->operando2->toPlainText().toFloat();
    operandoBin1 = getBinary32(operando1, &operando1bitstring);
    operandoBin2 = getBinary32(operando2, &operando2bitstring);

    std::string operacion = ui->comboBoxOperacion->currentText().toStdString();

    if(operacion == "+"){
        result = myAlu.suma(operandoBin1, operandoBin2);
    }else if(operacion == "x"){
        result = myAlu.producto(operandoBin1, operandoBin2);
    }else if(operacion == "/"){
        result = myAlu.division(operandoBin1, operandoBin2);
    }

    for(i = 1; i <= 32; i++){
        resultbitstring.append((char*) result[i]);
    }

    ui->operando1Hex->setText(QString::fromStdString(operando1bitstring));
    ui->operando2Hex->setText(QString::fromStdString(operando2bitstring));
    ui->resultadoHex->setText(QString::fromStdString(operando2bitstring));
}
