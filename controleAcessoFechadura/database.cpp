#include "database.h"

DataBase::DataBase()
{
    dataBase = QSqlDatabase::addDatabase("QSQLITE");
}

QString DataBase::DataBaseLocal()
{
    QString dataBaseDir = "C:/Users/carol/Documents/PRG22107/database/sistema_seguranca.db";

    return dataBaseDir;
}

bool DataBase::open()
{
    QString dataBaseDir = DataBase::DataBaseLocal();

    QFileInfo check_file(dataBaseDir);

    if (!check_file.exists()) {
        return false;
    }

    dataBase.setDatabaseName(dataBaseDir);
    dataBase.open();

    return dataBase.isOpen();
}

void DataBase::close()
{
    dataBase.close();
}
