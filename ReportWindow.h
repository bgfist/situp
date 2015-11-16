#ifndef REPORTWINDOW_H
#define REPORTWINDOW_H

#include <QMainWindow>
#include "Log.h"
#include <QList>
namespace Ui {
class ReportWindow;
}

class ReportWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit ReportWindow(QWidget *parent = 0,QList<Log> reportSet);

    ~ReportWindow();

private:
    Ui::ReportWindow *ui;


    void setTable(QList<Log>);
};

#endif // REPORTWINDOW_H
