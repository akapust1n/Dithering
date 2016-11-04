#include <DataManager.h>
#include <iostream>
//открываем изображение и приводим его к 8ми-битному
//не очень хорошая логика, но пойдет
QImage* DataManager::openImage(QString filename)
{

    QImage* image1 = new QImage(filename);
    cout << image1->depth();

    //cout<<image1->depth();
    //convertTo4Bit(image1);

    return image1;
}

DataManager::~DataManager()
{
    delete imageDithered;
    delete imageForDith;
    delete imageSample;
}

void DataManager::convertTo4Bit(QImage*& image)
{
    *image = image->convertToFormat(QImage::Format_Indexed8, Qt::AvoidDither);
    image->save(getImageName(NO_DITH));
}

void DataManager::loadImage(QString filename, DataManager::kind kindImage)
{
    QImage* openedImage = openImage(filename);
    QImage** temp2 = getImage(kindImage);
    *temp2 = openedImage;
    std::cout << "test;";
}

//неочевидная функция :)
QImage** DataManager::getImage(DataManager::kind kindImage)
{

    switch (kindImage) {
    case IMAGE_FOR_DITH: {
        return &imageForDith;
    }
    case IMAGE_DITHERED: {
        return &imageDithered;
    }
    case IMAGE_SAMPLE: {
        return &imageSample;
    }
    case IMAGE_BEFORE: {
        return &imageBefore;
    }
    default:
        return &imageBefore;
    };
    return nullptr;
}

 QString DataManager::getImageName(dither_kind kind)
{
    switch (kind) {
    case WHITE_DITH: {
        return (static_cast<QString>("white_noise_dith.bmp"));
    }
    case BROWN_DITH: {
        return  (static_cast<QString>("brown_noise_dit.bmp"));
    }
    case PINK_DITH: {
        return  (static_cast<QString>("pink_noise_dith.bmp"));
    }
    case VIOLET_DITH: {
        return  (static_cast<QString>("violet_noise_dith.bmp"));
    }
    case BLUE_DITH: {
        return  (static_cast<QString>("blue_noise_dith.bmp"));
    }
    case NO_DITH: {
        return  (static_cast<QString>("sample_img.bmp"));
    }
    default:
        return  (static_cast<QString>("before_conv.bmp"));
    };
}
