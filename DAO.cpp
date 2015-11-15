#include "DAO.h"

DAO::DAO()
{

}

void DAO::insert(Log log)
{
     CDatabase db =CDatabase::getDB();
     //do some sql operation







     db.CloseDB();

}

