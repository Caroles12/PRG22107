#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void escolheModoDeEntrada(int portaEscolhida);

private slots:
    void on_btnPortaEntrada_clicked();

    void on_btnPortaEscritorio_clicked();

    void on_btnPortaGaragem_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
