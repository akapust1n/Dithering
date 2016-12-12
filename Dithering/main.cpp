#include "MainWindow.h"
#include <Magick++.h>
#include <QSurfaceFormat>
#include <QtWidgets/QApplication>
int main(int argc, char* argv[])
{
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setVersion(3,3);
    Magick::InitializeMagick(*argv);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
