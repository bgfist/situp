#include "cdatabase.h"
#include <QSqlError>
#include <QSqlDatabase>
#include <QDebug>

CDatabase::CDatabase()
{

}

bool CDatabase::__ConnectDatabase(const QString &cDatabaseType, const QString &cHostName, const QString &cDatabaseName, const QString &cUserName, const QString &cPassword)
{
    QSqlDatabase db = QSqlDatabase::addDatabase(cDatabaseType);
    db.setHostName(cHostName);
    db.setDatabaseName(cDatabaseName);
    db.setUserName(cUserName);
    db.setPassword(cPassword);
    if (db.open())
    {
        qDebug() << "Connect database succeed";
        return true;
    }

    qDebug() << "Connect database failed, DB cannot use";
    qDebug() << db.lastError().text();
    return false;
}

const QSqlDatabase CDatabase::getDB()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.isValid())
    {
        if (db.isOpen() || db.open())
        {
            qDebug() << "Connect database succeed";
        }

        qDebug() << "Connect database failed, DB cannot use";
        qDebug() << db.lastError().text();
    }
    else
    {
        CDatabase iDB;
        iDB.__ConnectDatabase();
    }

    // after connect, should use the new create connection
    db = QSqlDatabase::database();
    return db;
}

void CDatabase::CloseDB()
{
    QSqlDatabase db = QSqlDatabase::database();
    db.close();
}


