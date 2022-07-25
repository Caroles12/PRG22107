#ifndef DATABASE_H
#define DATABASE_H

#include <fstream>
#include <string>
#include <QFile>
#include <QMessageBox>
#include <QtSql>

class DataBase
{
public:
    DataBase();
    QString DataBaseLocal();
    bool open();
    void close();

    QSqlDatabase dataBase;
};

#endif // DATABASE_H
