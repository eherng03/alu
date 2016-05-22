#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <string.h>
#include <alu.h>
#include <vector>
#include <floatieee.h>

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

private slots:
    void on_runButton_clicked();

private:
    Ui::MainWindow *ui;
    float operando1;
    float operando2;
    floatIEEE* operandoBin1;
    floatIEEE* operandoBin2;
    floatIEEE result;
    alu myAlu;
};

#endif // MAINWINDOW_H
