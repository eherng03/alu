#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <limits.h>
#include <iostream>
#include <math.h>
#include <bitset>
#include <string>
#include <string.h>
#include <vector>
#include <floatieee.h>

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







void MainWindow::on_runButton_clicked()
{
    int i;
    operando1 = ui->operando1->toPlainText().toFloat();
    operando2 = ui->operando2->toPlainText().toFloat();
    operandoBin1 = new floatIEEE(operando1);
    operandoBin2 = new floatIEEE(operando2);


    std::string operando1Hex = operandoBin1->getHexadecimal();
    //std::string jamon = operandoBin1->getHexadecimal();

    std::string operacion = ui->comboBoxOperacion->currentText().toStdString();

    if(operacion == "+"){
        *result = myAlu.suma(operandoBin1, operandoBin2);
    }else if(operacion == "x"){
        *result = myAlu.producto(operandoBin1, operandoBin2);
    }else if(operacion == "/"){
        *result = myAlu.division(operandoBin1, operandoBin2);
    }

    //ui->operando1Hex->setText(QString::fromStdString(lexical_cast<std::string>(binary2Hex(operandoBin1.aCadena())));
    //ui->operando2Hex->setText(QString::fromStdString(operando2bitstring));
    //ui->resultadoHex->setText(QString::fromStdString(operando2bitstring));
}
