#include <MainManager.h>

void MainManager::loadImage(QString filename)
{
    dataManager.loadImage(filename,DataManager::start_image);
    ditherManager.initImages(dataManager.getImage(DataManager::start_image),dataManager.getImage(DataManager::dithered_image));
}

void MainManager::dither(DitherManager::kind_dither kindDither)
{
    ditherManager.Dither(kindDither);
}
