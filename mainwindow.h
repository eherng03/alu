#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <string.h>
#include <alu.h>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int binary2Hex(std::string Binary);
    float getFloat32(std::string Binary);
    std::vector<int> getBinary32(float value, std::string *cadena);


private slots:
    void on_runButton_clicked();

private:
    Ui::MainWindow *ui;
    float operando1;
    float operando2;
    std::vector<int> operandoBin1;
    std::vector<int> operandoBin2;
    std::vector<int> result;
    std::string operando1bitstring;
    std::string operando2bitstring;
    std::string resultbitstring;
    alu myAlu;
};

#endif // MAINWINDOW_H
