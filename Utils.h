#ifndef UTILS_H
#define UTILS_H

#include <string>
using namespace std;
class Utils
{
public:
    static string int2str(int n) {

        char t[10];
        itoa(n,t,10);
        return string(t);
     }

};

#endif // UTILS_H
