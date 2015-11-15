#ifndef CDATABASE_H
#define CDATABASE_H

#include <QSqlDatabase>


class CDatabase
{
public:
    static const QSqlDatabase getDB();
    static void CloseDB();
private:
    CDatabase();
    bool __ConnectDatabase(const QString & cDatabaseType = "QMYSQL", const QString & cHostName = "localhost", const QString & cDatabaseName = "neck", const QString & cUserName = "root", const QString & cPassword = "");
};

#endif // CDATABASE_H
