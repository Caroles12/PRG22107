#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controleacessofechadura.h"
#include "database.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Escolhe Modo de Entrada da Fechadura");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::escolheModoDeEntrada(int portaEscolhida){
    DataBase dataBase;
    if(dataBase.open()){
        this->close();
        ControleAcessoFechadura controleAcessoFechadura;
        controleAcessoFechadura.setPortaEscolhida(portaEscolhida);
        controleAcessoFechadura.exec();
    }
}

void MainWindow::on_btnPortaEntrada_clicked()
{
    int portaEscolhida = 1;
    escolheModoDeEntrada(portaEscolhida);
}


void MainWindow::on_btnPortaEscritorio_clicked()
{
    int portaEscolhida = 2;
    escolheModoDeEntrada(portaEscolhida);
}


void MainWindow::on_btnPortaGaragem_clicked()
{
    int portaEscolhida = 3;
    escolheModoDeEntrada(portaEscolhida);
}

