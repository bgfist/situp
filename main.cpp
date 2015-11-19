#include "MainWindow.h"
#include <QApplication>


#include "cdatabase.h"
#include "Log.h"
#include "DAO.h"





int main(int argc, char *argv[])
{
   QApplication a(argc, argv);


   MainWindow w;
   w.show();




    return a.exec();
}


