#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "controleagente.h"
#include "database.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Login");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnCancelar_clicked()
{
    this -> close();
}


void MainWindow::checkLogin(){
    QString username = ui->userNameLogin->text();
    QString password = ui->passw->text();

    QSqlQuery query;

    if(query.exec("select * from LOGINAGENTES where USERLOGIN='"+username+"' and PASSWORD='"+password+"'")){
           if(query.next()){
                this->close();
                query.exec("UPDATE LOGINAGENTES SET AGENTELOGADO='1' WHERE USERLOGIN='"+username+"'");
                ControleAgente controleAgente;
                controleAgente.statusPorta();
                controleAgente.exec();
           }
           else{
               QMessageBox::about(this, "Login", "Usuário ou senha incorretos, por favor, tente novamente.");
               //Colocar um controle de login aqui
           }
       }
   // this -> close();

}

void MainWindow::on_btnOk_clicked()
{
    DataBase database;
    if(database.open()){
        checkLogin();
    }
}

