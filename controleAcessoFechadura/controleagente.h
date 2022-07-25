#ifndef CONTROLEAGENTE_H
#define CONTROLEAGENTE_H

#include <QDialog>
#include <QInputDialog>
#include <iostream>
#include <vector>
#include <iterator>

using std::vector;

namespace Ui {
class ControleAgente;
}

class ControleAgente : public QDialog
{
    Q_OBJECT

public:
    explicit ControleAgente(QWidget *parent = nullptr);
    ~ControleAgente();
    void getRegistroAcesso();
    void escolhePorta(QString operacao);
    void habilitaAcaoPorta(vector<int> &portaSelecionada, QString operacao);
    QString getAgenteLogado();
    QString getDataAtual();
    void statusPorta();
    void acionarAlarme();
    void setPortaEntrada(QString porta);
    void setPortaGaragem(QString porta);
    void setPortaEscritorio(QString porta);
    QString getStatusPortaEntrada();
    QString getStatusPortaGaragem();
    QString getStatusPortaEscritorio();
    void  removerUsuario();

private slots:
    void on_btnControleAcesso_clicked();

   // void on_btnAcionarAlarme_clicked();

  //  void on_btnHabilitarFechadura_clicked();

    void on_btnHabilitarFechadura_2_clicked();

   // void on_pushButton_clicked();


    void on_btnCadastrarUsuario_clicked();

    void on_btnAcionarAlarmeGeral_clicked();

    void on_btnRemoverUsuario_clicked();

private:
    Ui::ControleAgente *ui;
    QString portaEntrada;
    QString portaGaragem;
    QString portaEscritorio;
};

#endif // CONTROLEAGENTE_H
