#include "DitherManager.h"

void DitherManager::Dither(DitherManager::kind_dither kindDither)
{
    switch (kindDither) {
    case white_noise:{
        whiteNoiseDithering.Dither(image1, image2);
    }

    };
}

void DitherManager::initImages(std::shared_ptr<QImage> _image1, std::shared_ptr<QImage> _image2)
{
    image1=_image1;
    image2 = _image2;
}
