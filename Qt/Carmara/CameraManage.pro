#-------------------------------------------------
#
# Project created by QtCreator 2017-08-15T01:02:49
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CameraManage
TEMPLATE = app


SOURCES += main.cpp\
        cameramanage.cpp

HEADERS  += cameramanage.h

FORMS    += cameramanage.ui


INCLUDEPATH+= D:\opencv\build\include\opencv  \
              D:\opencv\build\include\opencv2 \
              D:\opencv\build\include

LIBS += -L D:\opencv\build\x86\mingw\lib\libopencv_*.a
