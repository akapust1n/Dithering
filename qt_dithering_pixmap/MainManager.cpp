#include <MainManager.h>
void MainManager::loadFile(QString& fname, DataManager::kind kindImage)
{
   dataManager.loadImage(fname, kindImage);
}

void MainManager::dither(dither_kind kind)
{
    ditherManager.dither(kind);
}

void MainManager::init(DataManager::kind kindImage)
{
    QImage *temp = *dataManager.getImage(kindImage);
    ditherManager.initImage(temp);
}

void MainManager::changeDepth(int depthk, DataManager::kind kindImage)
{
    //тут в теории можно будет изменять глубину цвета
    QImage *temp = *dataManager.getImage(kindImage);
    dataManager.convertTo4Bit(temp);
}

void MainManager::initSampleImage()
{
    metrics.initFirstImage(dataManager.getImage(DataManager::IMAGE_SAMPLE));
}

void MainManager::initDitheredImage()
{
    metrics.initSecondImage(dataManager.getImage(DataManager::IMAGE_DITHERED));
}

double MainManager::getSSIM()
{
   metrics.getSSIM();
}
