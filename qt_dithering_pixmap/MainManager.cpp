#include <MainManager.h>
void MainManager::loadFile(QString& fname, QImage *&image1)
{
    image1 = dataManager.openImage(fname);

}

void MainManager::dither(dither_kind kind)
{
    ditherManager.dither(kind);
}

void MainManager::init(QImage *image)
{
    ditherManager.initImage(image);
}

void MainManager::changeDepth(int depth,QImage *image)
{
    //тут в теории можно будет изменять глубину цвета
    dataManager.convertTo4Bit(image);
}
