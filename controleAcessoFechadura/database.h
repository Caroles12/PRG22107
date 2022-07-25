#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QMessageBox>
#include <QFile>
#include <string>
#include <fstream>

#include "mainwindow.h"

class DataBase
{
private:
    QString name;
public:
    DataBase();
    QString DataBaseLocal();
    bool open();
    void close();

    QSqlDatabase dataBase;
};

#endif // DATABASE_H
