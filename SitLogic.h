#ifndef SITLOGIC_H
#define SITLOGIC_H


#include "cpredictor.h"
#include "cserialreader.h"
#include <QString>
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

    static  QString fetchJudgedMessage(CPredictor::eSitType sitType =stType)
    {
        switch (sitType) {
        case CPredictor::NORMAL:
            return "Normal";
            break;
        case CPredictor::LEFTWARD:
            return "Leftward";
            break;
        case CPredictor::RIGHTWARD:
            return "Rightward";
            break;
        case CPredictor::BACKWARD:
            return "Backward";
            break;
        case CPredictor::FORWARD:
            return "Forward";

        }

    }

private:
    static CPredictor::eSitType stType  =CPredictor::NORMAL;
};

#endif // SITLOGIC_H
