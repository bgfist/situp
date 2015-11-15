#ifndef LOG_H
#define LOG_H



#include "User.h"
#include <QDate>
#include <QTime>
#include <FaceLogic.h>
#include "cpredictor.h"
/**
   domain object ,represent a record of database table log.

*/
struct  Log
{

public:
    int id;
    QDate  date;
    QTime  start_t;
    QTime  end_t;

    FacePostureType face_type;
    CPredictor::eSitType sit_type;

    User user;



};



#endif // LOG_H
