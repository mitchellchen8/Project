#include "cameramanage.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CameraManage w;
    w.show();

    return a.exec();
}
