#ifndef SITLOGIC_H
#define SITLOGIC_H


#include "cpredictor.h"
#include "cserialreader.h"

class SitLogic
{
public:
    SitLogic();

    static  eSitType getSitType()
    {
         return stType;
    }

    static void readOne()
    {
        CPredictor predictor;
        CSerialReader reader;
        stType =predictor.Predict(reader.ReadSerial());
    }

private:
    static eSitType stType  =NORMAL;
};

#endif // SITLOGIC_H
