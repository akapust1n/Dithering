#include <MainManager.h>

void MainManager::loadImage(QString filename)
{
    dataManager.loadImage(filename,DataManager::start_image);
}
