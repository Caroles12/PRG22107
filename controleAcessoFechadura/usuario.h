#ifndef USUARIO_H
#define USUARIO_H

#include <QDialog>
#include <vector>
#include <iterator>

using std::vector;

namespace Ui {
class Usuario;
}

class Usuario : public QDialog
{
    Q_OBJECT

public:
    explicit Usuario(QWidget *parent = nullptr);
    ~Usuario();
    void setNomeUsuario(QString nomeUsuario);
    QString getNomeUsuario();
    void setSenha(QString senha);
    QString getSenha();
    void setTagRfid(QString tagRfid);
    QString getTagRfid();
    void setDepartamento(QString departamento);
    QString getDepartamento();
    void  cadastrarUsuario(QString nomeUsuario, QString senha, QString tagRfid, QString departamento, vector<int> &portaSelecionada);
    void removerUsuarioCadastrado(QString nomeUsuario);

    private slots:
        void on_Confirma_clicked();

    void on_Cancela_clicked();

private:
    Ui::Usuario *ui;
    QString nomeUsuario;
    QString senha;
    QString tagRfid;
    QString departamento;
};

#endif // USUARIO_H
