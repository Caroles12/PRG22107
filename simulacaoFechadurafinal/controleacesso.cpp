#include "controleacesso.h"
#include "ui_controleacesso.h"
#include "database.h"
#include <QInputDialog>

#include <iostream>
using namespace std;

ControleAcesso::ControleAcesso(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControleAcesso)
{
    ui->setupUi(this);
    setWindowTitle("Controle de Acesso Fechadura");
    numeroDeTentativas = 0;
}

ControleAcesso::~ControleAcesso()
{
    delete ui;
}

void ControleAcesso::setPortaEscolhida(int portaEscolhida){
    this->portaEscolhida = portaEscolhida;
}

int ControleAcesso::getPortaEscolhida(){
    return this ->portaEscolhida;
}

void ControleAcesso::setNumeroDeTentativas(int numeroDeTentativas){
    this->numeroDeTentativas = numeroDeTentativas;
}

int ControleAcesso::getNumeroDeTentativas(){
    return this ->numeroDeTentativas;
}

void ControleAcesso::insereRegistroAcesso(QString Nome, int portaEscolhida, QString modoDeAcesso,bool entradaPermitida){
    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("dd.MM.yyyy hh:mm:ss");
    QSqlQuery query;
    query.prepare("INSERT INTO REGISTROACESSOS (username,date,acessMode,alarmeAcionado,portaEscolhida)"
                  "VALUES (:username,:date,:acessMode,:alarmeAcionado,:portaEscolhida)");
    query.bindValue(":username",Nome);
    query.bindValue(":date",formattedTime);
    query.bindValue(":acessMode",modoDeAcesso);
    query.bindValue(":alarmeAcionado",entradaPermitida);
    query.bindValue(":portaEscolhida",portaEscolhida);
    query.exec();
}

bool ControleAcesso::verificaAcessoSenha(QString senha){
    QSqlQuery query;
    portaEscolhida = getPortaEscolhida();
    query.exec("select Nome,PORTA1PERMITIDA,PORTA2PERMITIDA,PORTA1PERMITIDA from USUARIO where Senha='"+senha+"'");
    if(query.next()){
        QString nomeUsuario = query.value(0).toString();
        int porta1permitida = query.value(1).toInt();
        int porta2permitida = query.value(2).toInt();
        int porta3permitida = query.value(3).toInt();

        if(porta1permitida || porta2permitida || porta3permitida == portaEscolhida) {
            bool entradaPermitida = true;
            insereRegistroAcesso(nomeUsuario,portaEscolhida,"Senha", entradaPermitida);
            cout << "deu bom" << endl;
            return true;
        }
        else{
            return false;
        }
    }else{
        QMessageBox::about(this, "Senha incorreta", "Digite sua senha novamente");
        setNumeroDeTentativas(getNumeroDeTentativas()+1);
        if(getNumeroDeTentativas() == 3) {
            bool entradaPermitida = true;
            QMessageBox::about(this, "ACESSO BLOQUEADO", "Acesso Bloqueado");
            insereRegistroAcesso(NULL,portaEscolhida,"senha",entradaPermitida);
            this -> close();
        }
        return false;
    }
}

bool ControleAcesso::verificaAcessoRFID(QString numeroTagRfid){
    QSqlQuery query;
    portaEscolhida = getPortaEscolhida();
    query.exec("select Nome,PORTA1PERMITIDA,PORTA2PERMITIDA,PORTA1PERMITIDA from USUARIO where TAGRFID='"+numeroTagRfid+"'");
    if(query.next()){
        QString nomeUsuario = query.value(0).toString();
        int porta1permitida = query.value(1).toInt();
        int porta2permitida = query.value(2).toInt();
        int porta3permitida = query.value(3).toInt();

        if(porta1permitida || porta2permitida || porta3permitida == portaEscolhida) {
            bool entradaPermitida = true;
            insereRegistroAcesso(nomeUsuario,portaEscolhida,"Tag RFID", entradaPermitida);
            cout << "deu bom" << endl;
            return true;
        }
        else{
            return false;
        }
    }else{
        QMessageBox::about(this, "Tag Incorreta", "Problemas na leitura da Tag");
        setNumeroDeTentativas(getNumeroDeTentativas()+1);
        if(getNumeroDeTentativas() == 3) {
            bool entradaPermitida = true;
            QMessageBox::about(this, "ACESSO BLOQUEADO", "Acesso Bloqueado");
            insereRegistroAcesso(NULL,portaEscolhida,"senha",entradaPermitida);
            this -> close();
        }
        return false;
    }
}

void ControleAcesso::on_btnSenha_clicked()
{
    bool ok;

    QString senha = QInputDialog::getText(0, "Entrada por senha",
                                          "Digite a senha", QLineEdit::Normal,
                                          "", &ok);
    if (ok && !senha.isEmpty()) {
        bool acessoPermitido = verificaAcessoSenha(senha);
        if(acessoPermitido) {
             QMessageBox::about(this, "Bem-vindo", "Olá, seja bem vindo!");
             this -> close();
        }
    }
}


void ControleAcesso::on_btnTagRfid_clicked()
{
    bool ok;

    QString numeroTagRfid = QInputDialog::getText(0, "Entrada por TAGRFID",
                                          "Utilize a tagRFID", QLineEdit::Normal,
                                          "", &ok);

    if (ok && !numeroTagRfid.isEmpty()) {
        bool acessoPermitido = verificaAcessoRFID(numeroTagRfid);
        if(acessoPermitido) {
             QMessageBox::about(this, "Bem-vindo", "Olá, seja bem vindo!");
             this -> close();
        }
    }
}

