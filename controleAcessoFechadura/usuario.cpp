#include "usuario.h"
#include "ui_usuario.h"
#include "database.h"


Usuario::Usuario(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Usuario)
{
    ui->setupUi(this);
    setWindowTitle("Cadastrar Usuário");
}

Usuario::~Usuario()
{
    delete ui;
}

void Usuario::setNomeUsuario(QString nomeUsuario){
    this->nomeUsuario = nomeUsuario;
}

QString Usuario::getNomeUsuario(){
    return this ->nomeUsuario;
}

void Usuario::setSenha(QString senha){
    this->senha = senha;
}

QString Usuario::getSenha(){
    return this ->senha;
}

void Usuario::setTagRfid(QString tagRfid){
    this->tagRfid = tagRfid;
}

QString Usuario::getTagRfid(){
    return this ->tagRfid;
}

void Usuario::setDepartamento(QString departamento){
    this->departamento = departamento;
}

QString Usuario::getDepartamento(){
    return this ->departamento;
}

void Usuario::cadastrarUsuario(QString nomeUsuario, QString senha, QString tagRfid, QString departamento, vector<int> &portaSelecionada) {
    QSqlQuery query;
    int numeroUltimoUserId = 0;
    int novoIdUsuario = 0;

    query.exec("SELECT USERID FROM USUARIO ORDER BY USERID DESC");
    if(query.next()){
        numeroUltimoUserId = query.value(0).toInt();
        novoIdUsuario = numeroUltimoUserId + 1;
    }

    QString senhaFinal = QString::number(novoIdUsuario) + senha;

    query.prepare("INSERT INTO USUARIO (Nome,Senha,TagRFID,Departamento,PORTA1PERMITIDA,PORTA2PERMITIDA,PORTA3PERMITIDA) "
                  "VALUES (:Nome,:Senha,:TagRFID,:Departamento,:PORTA1PERMITIDA,:PORTA2PERMITIDA,:PORTA3PERMITIDA)");
    query.bindValue(":Nome",nomeUsuario);
    query.bindValue(":Senha",senhaFinal);
    query.bindValue(":TagRFID",tagRfid);
    query.bindValue(":Departamento",departamento);
    query.bindValue(":PORTA1PERMITIDA",portaSelecionada[0]);
    query.bindValue(":PORTA2PERMITIDA",portaSelecionada[1]);
    query.bindValue(":PORTA3PERMITIDA",portaSelecionada[2]);
    query.exec();
    QMessageBox::about(this, "Cadastrar Usuário", "Usuário cadastrado \n Sua nova senha é: " + senhaFinal);
    this->close();
}

void Usuario::removerUsuarioCadastrado(QString nomeUsuario){
    QSqlQuery query;

    if(query.exec("DELETE from USUARIO where Nome='"+nomeUsuario+"'")){
        QMessageBox::about(this, "Remover Usuário", "Usuário Removido ");
    }
}

void Usuario::on_Confirma_clicked()
{
    QSqlQuery query;


    setNomeUsuario(ui ->NomedeUsuario->text());
    setSenha(ui ->SenhaUsuario->text());
    setTagRfid(ui ->TagRFID -> text());
    setDepartamento(ui -> Departamento -> text());

    bool checkbox[3];
    vector<int> portaSelecionada = {0,0,0};
    checkbox[0] = ui ->PortaDiretoria -> isChecked();
    checkbox[1] = ui ->PortaEntrada -> isChecked();
    checkbox[2] = ui ->PortaEscritorio -> isChecked();
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

    cadastrarUsuario(getNomeUsuario(), getSenha(), getTagRfid(), getDepartamento(),portaSelecionada);


}


void Usuario::on_Cancela_clicked()
{
    this->close();
}

