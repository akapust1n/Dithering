#include "DataManager.h"

void DataManager::loadImage(QString filename, kind kindImage)
{

    switch (kindImage) {
    case (start_image): {
        start_image1.reset(new QImage(filename));
        start_image1->save(getImageName(kindImage));
        break;
    }
    case (converted_image):
        converted_image1.reset(new QImage(filename));
        break;
    default:
        dithered_image1.reset(new QImage(filename));
    }
    return;
}

 std::shared_ptr<QImage> DataManager::getImage(DataManager::kind kindImage)
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
