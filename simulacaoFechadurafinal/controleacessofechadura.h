#ifndef CONTROLEACESSOFECHADURA_H
#define CONTROLEACESSOFECHADURA_H

#include <QDialog>

namespace Ui {
class ControleAcessoFechadura;
}

class ControleAcessoFechadura : public QDialog
{
    Q_OBJECT

public:
    explicit ControleAcessoFechadura(QWidget *parent = nullptr);
    ~ControleAcessoFechadura();
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
    Ui::ControleAcessoFechadura *ui;
    int portaEscolhida;
    int numeroDeTentativas;
};

#endif // CONTROLEACESSOFECHADURA_H
