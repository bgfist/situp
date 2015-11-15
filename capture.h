#ifndef CAPTURE
#define CAPTURE

#include <iostream>
#include <vector>
#include <QImage>
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <fstream>
using namespace std;


//打开摄像头
string openCamera();

//从摄像头抓取照片
string capture();

//关闭摄像头
void closeCamera();

//抓取图片，返回qt形式的图片
QImage detect();

//清尾工作，关闭打开的opencv窗口
void exitApp();

//工具方法，将整数转成字符串
string int2str(int n);

//工具方法，将源字符串切割成字符串vector
vector<string> split(const string& src, string delimit, string null_subst="");

//是否允许摄像头打开
bool isAllowCameraOpen();

//允许摄像头打开
void allowCameraOpen();

QImage cvMat2QImage(const cv::Mat& mat);

cv::Mat QImage2cvMat(QImage image);
#endif // CAPTURE

