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
    void checkLogin();

private slots:
    void on_btnCancelar_clicked();

    void on_btnOk_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
