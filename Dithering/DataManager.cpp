#include "DataManager.h"

void DataManager::loadImage(QString filename, kind kindImage)
{
    start_image1.reset(new QImage(filename));
    start_image1->save(getImageName(kindImage));
}

void DataManager::loadImage(std::shared_ptr<QImage>& image, DataManager::kind kindImage)
{
    switch (kindImage) {
    case (converted_image):
        converted_image1 = image;
        break;
    default:
        dithered_image1 = image;
    }
}

std::shared_ptr<QImage>& DataManager::getImage(DataManager::kind kindImage)
{
    switch (kindImage) {
    case (start_image):
        return start_image1;
    case (converted_image):
        return converted_image1;
    default:
        return dithered_image1;
    }
}

QString DataManager::getImageName(DataManager::kind kindImage)
{
    switch (kindImage) {
    case (start_image):
        return (static_cast<QString>("start_image.bmp"));
    case (converted_image):
        return (static_cast<QString>("converted_image.bmp"));
    default:
        return (static_cast<QString>("dithered_image.bmp"));
    }
}
