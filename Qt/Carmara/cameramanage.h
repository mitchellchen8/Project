#ifndef CAMERAMANAGE_H
#define CAMERAMANAGE_H

#include <QMainWindow>
#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QTimer>     // 设置采集数据的间隔时间
#include <iostream>
#include <iterator>
#include <vector>

#include "opencv2/highgui/highgui.hpp"  //包含opencv库头文件
#include "opencv/cv.h"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

namespace Ui {
class CameraManage;
}

class CameraManage : public QMainWindow
{
    Q_OBJECT

public:
    explicit CameraManage(QWidget *parent = 0);
    ~CameraManage();
    QImage  Mat2QImage(Mat& cvImg);
    QImage  ScaleImage2Label(QImage qImage, QLabel* qLabel);

private slots: 
    void openCamera();      // 打开摄像头
    void readFarme();            // 读取当前帧信息

private:
    Ui::CameraManage *ui;
    QTimer  *timer;
    QImage imageL;
    QImage imageR;
    Mat frameL;
    Mat frameR;
    VideoCapture capL;
    VideoCapture capR;
    qint32 count;
};

#endif // CAMERAMANAGE_H
