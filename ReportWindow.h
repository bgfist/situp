#ifndef REPORTWINDOW_H
#define REPORTWINDOW_H

#include <QMainWindow>
#include "Log.h"
namespace Ui {
class ReportWindow;
}

class ReportWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit ReportWindow(QWidget *parent = 0,vector<Report> reportSet =vector<Report>());

    ~ReportWindow();

private:
    Ui::ReportWindow *ui;


    void setTable(vector<Report>);
};

#endif // REPORTWINDOW_H
