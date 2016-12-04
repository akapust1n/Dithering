#include "DitherManager.h"
#include <iostream>


void DitherManager::Dither(DitherManager::kind_dither kindDither)
{
     std::chrono::time_point<std::chrono::system_clock> start, end;
     start = std::chrono::system_clock::now();
    switch (kindDither) {
    case white_noise: {
        whiteNoiseDithering.Dither(image1, image2);
        break;
    }
    case blue_noise: {
        blueNoiseDithering.Dither(image1, image2);
        break;
    }
    case violet_noise: {
        violetNoiseDithering.Dither(image1, image2);
        break;
    }
    case pink_noise: {
        pinkNoiseDithering.Dither(image1, image2);
        break;
    }
    case brown_noise: {
        brownNoiseDithering.Dither(image1, image2);
        break;
    }
    case floyd_sd: {
        floydSDDithering.Dither(image1,image2);
        break;
    }
    case false_floyd_sd: {
        falseFloydSDDithering.Dither(image1,image2);
        break;
    }
    case jjn:{
        jjnDithering.Dither(image1,image2);
        break;
    }
    case yliluoma1:{
        yliluoma1Dithering.Dither(image1, image2);
        break;
    }

    default:
        whiteNoiseDithering.Dither(image1, image2);
    };
    end = std::chrono::system_clock::now();
    last_elapsed_seconds = std::chrono::duration_cast<std::chrono::milliseconds>
                                 (end-start).count();
    if(!image2.get())
    std::cout<<"image2 is null in DitherManager"<<std::endl;

}

void DitherManager::initImages(std::shared_ptr<QImage> &_image1, std::shared_ptr<QImage> &_image2)
{
    image1 = _image1;
    if(!_image1.get())
        std::cout<<"image1 is null in initImages"<<std::endl;
    if(!_image2.get())
        std::cout<<"image2 is null in initImages"<<std::endl;
    image2 = _image2;
}

QString DitherManager::getImageName(DitherManager::kind_dither kindDither)
{
    switch (kindDither) {
    case white_noise: {
        return (static_cast<QString>("white_noise_dith.bmp"));
    }
    case brown_noise: {
        return (static_cast<QString>("brown_noise_dit.bmp"));
    }
    case pink_noise: {
        return (static_cast<QString>("pink_noise_dith.bmp"));
    }
    case violet_noise: {
        return (static_cast<QString>("violet_noise_dith.bmp"));
    }
    case blue_noise: {
        return (static_cast<QString>("blue_noise_dith.bmp"));
    }
    case floyd_sd: {
        return (static_cast<QString>("floydsd_noise_dith.bmp"));
    }
    case false_floyd_sd: {
        return (static_cast<QString>("false_floydsd_noise_dith.bmp"));
    }
    case jjn: {
        return (static_cast<QString>("jjn_noise_dith.bmp"));
    }
    case yliluoma1: {
        return (static_cast<QString>("yliluoma1_noise_dith.bmp"));
    }
    default:
        return (static_cast<QString>("smth.bmp"));
    }
}

std::shared_ptr<QImage> &DitherManager::getImage()
{
    return image2;
}

int DitherManager::getTime()
{
    return last_elapsed_seconds;
}
