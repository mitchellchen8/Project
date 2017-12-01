#include "cameramanage.h"
#include "ui_cameramanage.h"
#include <QPixmap>
#include <QFileDialog>
#include <QPicture>
#include <iostream>
#include <QDateTime>
#include <QCameraInfo>


CameraManage::CameraManage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CameraManage)
{
    ui->setupUi(this);
    timer   = new QTimer(this);
    count = 0;
    openCamera();  //初始化时就打开摄像头

    /*信号和槽*/
    connect(timer, SIGNAL(timeout()), this, SLOT(readFarme()));  // 时间到，读取当前摄像头信息
}

CameraManage::~CameraManage()
{
    delete ui;
    delete timer;
}

QImage  CameraManage::Mat2QImage(Mat& cvImg)  // Mat格式转换为QImage格式
{
    QImage qImg;
    if(cvImg.channels()==3)                             //3 channels color image
    {

        cv::cvtColor(cvImg,cvImg,CV_BGR2RGB);
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols, cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_RGB888);
    }
    else if(cvImg.channels()==1)                    //grayscale image
    {
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols,cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_Indexed8);
    }
    else
    {
        qImg =QImage((const unsigned char*)(cvImg.data),
                    cvImg.cols,cvImg.rows,
                    cvImg.cols*cvImg.channels(),
                    QImage::Format_RGB888);
    }

    return qImg;

}

QImage CameraManage::ScaleImage2Label(QImage qImage, QLabel* qLabel) // 使图片能适应Lable部件
{
    QImage qScaledImage;
    QSize qImageSize = qImage.size();
    QSize qLabelSize = qLabel->size();
    double dWidthRatio = 1.0*qImageSize.width() / qLabelSize.width();
    double dHeightRatio = 1.0*qImageSize.height() / qLabelSize.height();
    if (dWidthRatio>dHeightRatio)
    {
        qScaledImage = qImage.scaledToWidth(qLabelSize.width());
    }
    else
    {
        qScaledImage = qImage.scaledToHeight(qLabelSize.height());
    }
    return qScaledImage;
}

void CameraManage::openCamera()
{
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
      foreach (const QCameraInfo &cameraInfo, cameras)
      {
          qDebug() << cameraInfo.description();
          qDebug() << cameraInfo.deviceName();
          qDebug() << cameraInfo.defaultCamera();
          qDebug() << cameraInfo.orientation();
      }
    qint32 camL=1;
    qint32 camR=2;
    qint32 driver=CV_CAP_DSHOW;

    capL.open(0);   //笔记本一般是0  open函数直接能打开USB摄像头，也能打开网络摄像头，具体参数，直接百度, 也能直接打开图片、视频
    capR.open(2);
    timer->start(33);              // 开始计时，超时则发出timeout()信号
}

void CameraManage::readFarme()
{
    capL >> frameL;
    capR >> frameR;
    imageL = Mat2QImage(frameL);
    imageR = Mat2QImage(frameR);
#if 0
    if(!(count%30))
    {
        QFile::remove("15108122*.png");
        image.save(QString::number(QDateTime::currentSecsSinceEpoch(),10)+".png");
    }
    count++;
#endif
    QImage scaleImageL = ScaleImage2Label(imageL, ui->lift_display);   // 显示到label上
    ui->lift_display->setPixmap(QPixmap::fromImage(scaleImageL));
    ui->lift_display->setAlignment(Qt::AlignCenter);
    QImage scaleImageR = ScaleImage2Label(imageR, ui->right_display);   // 显示到label上
    ui->right_display->setPixmap(QPixmap::fromImage(scaleImageR));
    ui->right_display->setAlignment(Qt::AlignCenter);
    ui->lift_display->show();
    ui->right_display->show();
}




