//dao
#include "DAO.h"
#include "cdatabase.h"

//qt sql
#include <QSqlQuery>
#include <QVariant>



DAO::DAO()
{

}

void DAO::insert(Log log,User user)
{
     QSqlDatabase db =CDatabase::getDB();
     //do some sql operation
     db.transaction();
     QSqlQuery query;

     query.prepare("INSERT INTO log (date, start_t, end_t,face_type,sit_type,userid) VALUES (:date, :start_t, :end_t,:face_type,:sit_type,:userid)");

     query.bindValue(":date", log.date);
     query.bindValue(":start_t", log.start_t);
     query.bindValue(":end_t", log.end_t);
     query.bindValue(":face_type",log.face_type);
     query.bindValue(":sit_type",log.sit_type);
     query.bindValue(":userid",user.userid);

     query.exec();




     db.commit();
     db.CloseDB();

}

QList<Log> DAO::query(QDate date, User user)
{
    QSqlDatabase db =CDatabase::getDB();
    //do some sql operation

    QSqlQuery query;
    query.prepare("select * from log where date=:date and userid=:userid");
    query.bindValue(":date",date);
    query.bindValue(":userid",user.userid);
    query.executedQuery();

    QList<Log>  logs;
    while (query.next()) {

        Log log;
        log.id        =query.value("id").toInt();
        //log.date      =query.value("date").toDate();
        log.start_t   =query.value("start_t").toTime();
        log.end_t     =query.value("end_t").toTime();
        log.face_type =query.value("face_type").toString();
        log.sit_type  =query.value("sit_type").toString();
        //log.user      =user;

        logs.insert(0,log);
    }


    db.close();

    return logs;


}

