#include "Log.h"

#include <fstream>
#include <string>
#include "capture.h"
#include <stdlib.h>




void writeReport(Report & report,const char *daystr)
{
    string path ="reports/";
    string ext =".txt";

    ofstream out((path+daystr+ext).c_str(),ios::app);
    out<<report.start<<"   "<<report.end<<"   "<<report.type<<"   "<<report.duration<<endl;
    out.close();
}





vector<Report> getReportByDay(const char *daystr)
{
    string path ="reports/";
    string ext =".txt";
    ifstream in((path+daystr+ext).c_str());

    vector<Report> reports;
    if(in.is_open())
    {
        string line;
        while(!in.eof())
        {
              getline(in,line);

              if(line.empty())
                  break;

              Report temp;
//              istringstream in(line);
//              in>>temp;

              vector<string> strs =split(line,"   ");
              temp.start =strs[0];
              temp.end =strs[1];
              temp.type =strs[2];
              temp.duration =atoi(strs[3].c_str());
              reports.push_back(temp);

        }

    }
    in.close();
    return reports;
}


const istringstream& operator>>(istringstream& in,Report& rt)
{
      char * temp;

      in>>temp;
      rt.start =temp;
      in>>temp;
      rt.end =temp;
      in>>temp;
      rt.type =temp;
      in>>rt.duration;
      return in;
}
