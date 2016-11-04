#include <MainManager.h>
void MainManager::loadFile(QString fname, DataManager::kind kindImage)
{
    dataManager.loadImage(fname, kindImage);
}

void MainManager::dither(dither_kind kind)
{
    ditherManager.dither(kind);
}

void MainManager::init(DataManager::kind kindImage)
{
    QImage* temp = *dataManager.getImage(kindImage);
    switch (kindImage) {
    case DataManager::IMAGE_SAMPLE:
        metrics.initFirstImage(dataManager.getImage(DataManager::IMAGE_SAMPLE));
        break;
    case DataManager::IMAGE_DITHERED:
        metrics.initSecondImage(dataManager.getImage(DataManager::IMAGE_DITHERED));
        break;
    case DataManager::IMAGE_FOR_DITH:
        ditherManager.initImage(temp);
        break;
    }
}

void MainManager::saveAsFiles(int depthk, DataManager::kind kindImage)
{
    //тут в теории можно будет изменять глубину цвета
    QImage* temp = *dataManager.getImage(kindImage);
    //save original image
    temp->save(DataManager::getImageName());
    dataManager.convertTo4Bit(temp);

}



double MainManager::getSSIM()
{
    return metrics.getSSIM();
}

double MainManager::getPSNR()
{
    return metrics.getPSNR();
}
