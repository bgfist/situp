#ifndef LOG_H
#define LOG_H

#include <vector>
#include <sstream>
#include <cstring>
#include <string>
using namespace std;
struct  Report
{

public:
    string  start;
    string  end;

    string type;
    int duration;


    Report():start(""),end(""),type(""),duration(0)
    {}

    Report(string start,string end,string type,int duration):start(start),end(end),type(type),duration(duration)
    {}


};


//写入记录
void writeReport(Report &,const char *daystr);

//抓取记录，按日期
vector<Report> getReportByDay(const char * daystr);

//操作符重载，便于日志存储
const istringstream& operator>>(istringstream& in,Report& rt);



#endif // LOG_H
