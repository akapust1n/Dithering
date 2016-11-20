#include "MainWindow.h"
#include <QApplication>
#include "ImageMagick-6/Magick++.h"

int main(int argc, char *argv[])
{
    Magick::InitializeMagick(*argv);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
