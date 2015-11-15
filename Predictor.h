#ifndef PREDICTOR
#define PREDICTOR


#include "User.h"
#include <QByteArray>

/**
  domain object:  represent a record in database table predictor.
 */
struct  Predictor
{
   int id;
   QByteArray xml;
   User user;

};
#endif // PREDICTOR

