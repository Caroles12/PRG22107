#include "controleagente.h"
#include "ui_controleagente.h"
#include "database.h"
#include "usuario.h"
#include <vector>

using std::vector;

ControleAgente::ControleAgente(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ControleAgente)
{
    ui->setupUi(this);
    setWindowTitle("Controle de Acesso");
    portaEntrada = "Fechada";
    portaEscritorio = "Fechada";
    portaGaragem = "Fechada";
}

ControleAgente::~ControleAgente()
{
    delete ui;
}

void ControleAgente::setPortaEntrada(QString porta){
    this->portaEntrada = porta;
}

void ControleAgente::setPortaGaragem(QString porta){
    this->portaGaragem = porta;
}

void ControleAgente::setPortaEscritorio(QString porta){
    this->portaEscritorio = porta;
}

QString ControleAgente::getStatusPortaEntrada(){
    return this ->portaEntrada;
}

QString ControleAgente::getStatusPortaGaragem(){
    return this ->portaGaragem;
}

QString ControleAgente::getStatusPortaEscritorio(){
    return this ->portaEscritorio;
}

void ControleAgente::statusPorta(){
    QSqlQuery query;
    query.exec("SELECT DOORNAME FROM PORTAS WHERE DOORSTATUS='1'");
    while(query.next()){
        QString doorName = query.value(0).toString();
        if(doorName == "Porta1") {
            setPortaEntrada("Aberta");
        }else if(doorName == "Porta2"){
            setPortaEscritorio("Aberta");
        }else{
            setPortaGaragem("Aberta");
        }
    }

    ui->labelEntrada->setText(getStatusPortaEntrada());
    ui->labelEscritorio->setText(getStatusPortaEscritorio());
    ui->labelGaragem->setText(getStatusPortaGaragem());
}


void ControleAgente::getRegistroAcesso(){
    QSqlQuery query;
    QFile agentFile("C:/Users/carol/Documents/PRG22107/relatorios/relatorioagente.txt");
    query.exec("SELECT * FROM REGISTROACESSOS ORDER BY recordId ASC");
    while(query.next()){
        if(agentFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
        {
            QTextStream stream(&agentFile);
            QString nomeUsuario = query.value(1).toString();
            bool alarmeAcionado = query.value(4).toBool();
            int portaUtilziada = query.value(5).toInt();
            QString alarme;
            QString porta;

            if(nomeUsuario.isEmpty()) {
                nomeUsuario = "Usuário sem registro";
            }

            if(alarmeAcionado){
                alarme = "Alarme Acionado";
            }else{
                alarme = "Alarme Desligado";
            }

            if(portaUtilziada == 1) {
                porta = "Porta da Entrada";
            }else if(portaUtilziada == 2){
                porta = "Porta do Escritório";
            }else{
                porta = "Porta da Garagem";
            }

            stream << "Número do Registro" << ": " << "" << query.value(0).toString() << ", "
                   << "Nome de usuário" << ": " << "" << nomeUsuario << ", "
                   << "Data" << ": " << "" << query.value(2).toString() << ", "
                   << "Modo de Acesso" << ": " << "" << query.value(3).toString() << ", "
                   << "Alarme Acionado" << ": " << "" << alarme << ", "
                   << "Porta Utilizada" << ": " << "" << porta<< "\n ";

            agentFile.close();
            qDebug() << "Writing finished";
        }
    }
    QMessageBox::about(this, "Registro de acessos", "Registro Gerado");
}

QString ControleAgente::getAgenteLogado(){
    QSqlQuery query;
    QString usuario;

    query.exec("SELECT USERLOGIN FROM LOGINAGENTES WHERE AGENTELOGADO='1'");
    if(query.next()){
        usuario = query.value(0).toString();
    }

    return usuario;
}

QString ControleAgente::getDataAtual(){
    QDateTime date = QDateTime::currentDateTime();
    QString formattedTime = date.toString("dd.MM.yyyy hh:mm:ss");

    return formattedTime;
}

void ControleAgente::habilitaAcaoPorta(vector<int> &portaSelecionada, QString operacao){
    QSqlQuery query;
    QString usuario = getAgenteLogado();
    QString date = getDataAtual();

    bool acionarAlarme = true;

    if(operacao == "entrar") {
        acionarAlarme = false;
    }

    if(portaSelecionada[0] == 1 ){
        query.exec("select DOORID from PORTAS where DOORNAME='Porta1'");
        if(query.next()){
            int doorId = query.value(0).toInt();
            query.prepare("UPDATE PORTAS SET DOORSTATUS='1' WHERE DOORID=:doorId");
            query.bindValue(":doorId", doorId);
            query.exec();
            query.prepare("INSERT INTO REGISTROACESSOS (username,date,acessMode,alarmeAcionado,portaEscolhida) "
                          "VALUES (:username,:date,:acessMode,:alarmeAcionado,:portaEscolhida)");
            query.bindValue(":username",usuario);
            query.bindValue(":date",date);
            query.bindValue(":acessMode","Acesso Central");
            query.bindValue(":alarmeAcionado",acionarAlarme);
            query.bindValue(":portaEscolhida",1);
            query.exec();
        }
    }

    if(portaSelecionada[1] == 1 ){
        query.exec("select DOORID from PORTAS where DOORNAME='Porta2'");
        if(query.next()){
            int doorId = query.value(0).toInt();
            query.prepare("UPDATE PORTAS SET DOORSTATUS='1' WHERE DOORID=:doorId");
            query.bindValue(":doorId", doorId);
            query.exec();
            query.prepare("INSERT INTO REGISTROACESSOS (username,date,acessMode,alarmeAcionado,portaEscolhida) "
                          "VALUES (:username,:date,:acessMode,:alarmeAcionado,:portaEscolhida)");
            query.bindValue(":username",usuario);
            query.bindValue(":date",date);
            query.bindValue(":acessMode","Acesso Central");
            query.bindValue(":alarmeAcionado",acionarAlarme);
            query.bindValue(":portaEscolhida",2);
            query.exec();
        }
    }

    if(portaSelecionada[2] == 1 ){
        query.exec("select DOORID from PORTAS where DOORNAME='Porta3'");
        if(query.next()){
            int doorId = query.value(0).toInt();
            query.prepare("UPDATE PORTAS SET DOORSTATUS='1' WHERE DOORID=:doorId");
            query.bindValue(":doorId", doorId);
            query.exec();
            query.prepare("INSERT INTO REGISTROACESSOS (username,date,acessMode,alarmeAcionado,portaEscolhida) "
                          "VALUES (:username,:date,:acessMode,:alarmeAcionado,:portaEscolhida)");
            query.bindValue(":username",usuario);
            query.bindValue(":date",date);
            query.bindValue(":acessMode","Acesso Central");
            query.bindValue(":alarmeAcionado",acionarAlarme);
            query.bindValue(":portaEscolhida",3);
            query.exec();
        }
    }

    if(acionarAlarme){
        QMessageBox::about(this, "Acionar Alarme", "ALARME ACIONADO");
    }else{
        QMessageBox::about(this, "Destravar Fechadura", "Fechadura Aberta");
    }
}

void ControleAgente::escolhePorta(QString operacao){
    bool checkbox[3];
    vector<int> portaSelecionada = {0,0,0};
    checkbox[0] = ui ->checkBoxEntrada -> isChecked();
    checkbox[1] = ui ->checkBoxEscritorio-> isChecked();
    checkbox[2] = ui ->checkBoxGaragem -> isChecked();
    for(int i=0;i<3;i++){
        if(checkbox[0]){
            portaSelecionada[0] = 1;
        }
        if(checkbox[1]){
            portaSelecionada[1] = 1;
        }
        if(checkbox[2]){
            portaSelecionada[2] = 1;
        }
    }
    habilitaAcaoPorta(portaSelecionada,operacao);

}

void ControleAgente::acionarAlarme(){
    QSqlQuery query;
    QString usuario = getAgenteLogado();
    QString date = getDataAtual();

    query.prepare("INSERT INTO REGISTROACESSOS (username,date,acessMode,alarmeAcionado,portaEscolhida) "
                  "VALUES (:username,:date,:acessMode,:alarmeAcionado,:portaEscolhida)");
    query.bindValue(":username",usuario);
    query.bindValue(":date",date);
    query.bindValue(":acessMode","Acesso Central");
    query.bindValue(":alarmeAcionado",1);
    query.bindValue(":portaEscolhida",1);
    query.exec();

    query.prepare("INSERT INTO REGISTROACESSOS (username,date,acessMode,alarmeAcionado,portaEscolhida) "
                  "VALUES (:username,:date,:acessMode,:alarmeAcionado,:portaEscolhida)");
    query.bindValue(":username",usuario);
    query.bindValue(":date",date);
    query.bindValue(":acessMode","Acesso Central");
    query.bindValue(":alarmeAcionado",1);
    query.bindValue(":portaEscolhida",2);
    query.exec();

    query.prepare("INSERT INTO REGISTROACESSOS (username,date,acessMode,alarmeAcionado,portaEscolhida) "
                  "VALUES (:username,:date,:acessMode,:alarmeAcionado,:portaEscolhida)");
    query.bindValue(":username",usuario);
    query.bindValue(":date",date);
    query.bindValue(":acessMode","Acesso Central");
    query.bindValue(":alarmeAcionado",1);
    query.bindValue(":portaEscolhida",3);
    query.exec();

    QMessageBox::about(this, "Acionamento de Alarme", "ALARME ACIONADO");

}

void ControleAgente:: removerUsuario(){
    bool ok;
    QString nomeUsuario = QInputDialog::getText(0, "Remover Usuário",
                                          "Digite o nome de usuário a ser removido", QLineEdit::Normal,
                                          "", &ok);
    if (ok && !nomeUsuario.isEmpty()) {
       Usuario usuario;
       usuario.removerUsuarioCadastrado(nomeUsuario);
    }
}
void ControleAgente::on_btnControleAcesso_clicked()
{
    getRegistroAcesso();
}


void ControleAgente::on_btnHabilitarFechadura_2_clicked()
{
    QString operacao = "entrar";
    escolhePorta(operacao);
}

void ControleAgente::on_btnCadastrarUsuario_clicked()
{
    Usuario usuario;
    usuario.exec();
}


void ControleAgente::on_btnAcionarAlarmeGeral_clicked()
{
    acionarAlarme();
}


void ControleAgente::on_btnRemoverUsuario_clicked()
{
    removerUsuario();
}

