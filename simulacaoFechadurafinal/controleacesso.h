#ifndef CONTROLEACESSO_H
#define CONTROLEACESSO_H

#include <QDialog>

namespace Ui {
class ControleAcesso;
}

class ControleAcesso : public QDialog
{
    Q_OBJECT

public:
    explicit ControleAcesso(QWidget *parent = nullptr);
    ~ControleAcesso();
    void setPortaEscolhida(int portaEscolhida);
    int getPortaEscolhida();
    void setNumeroDeTentativas(int numeroDeTentativas);
    int getNumeroDeTentativas();
    void insereRegistroAcesso(QString Nome, int portaEscolhida, QString modoDeAcesso, bool entradaPermitida);
    bool verificaAcessoSenha(QString senha);
    bool verificaAcessoRFID(QString numeroTagRfid);

private slots:
    void on_btnSenha_clicked();

    void on_btnTagRfid_clicked();

private:
    Ui::ControleAcesso *ui;
    int portaEscolhida;
    int numeroDeTentativas;
};

#endif // CONTROLEACESSO_H
