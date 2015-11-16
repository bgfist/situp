#pragma once
#ifndef FACELOGIC_H
#define FACELOGIC_H


#include "opencv2/core/core.hpp"
#include <QList>
#include <QString>
using namespace cv;

enum FacePostureType{ Normal, Profile,NO_FACE,Fault_FACE, Near, Far, Left, Right, Up, Down};

class FaceLogic
{
public:
	/**
	  存储初始（正常）坐标值，到文件
    */
    static bool storeNormalValue(const Point&,const Point&,const Point&);

	/**
	  获取坐标初始值
	*/
    static QList<Point> getNormalValue();

	/**
	  判断脸部姿势，返回一个枚举类型
	*/
    static void judgeFacePosture(const Point&,const Point&,const Point&);
	/**
      枚举类型转换为字符串
	*/
    static QString fetchJudgedMessage(FacePostureType faceType=rtType);


    /**
      rtType的getter和setter
    */
    static FacePostureType getRtType();
    static void setRtType(FacePostureType rtType);

private:
	//bool hasInitilized;
    static FacePostureType rtType;
    static QList<Point> normal;

public:
	static bool isInitialized();
};

#endif //FACELOGIC_H
