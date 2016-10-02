#include <DitherManager.h>

void DitherManager::initImage(QImage* _image1)
{
    image1 = _image1;
}

void DitherManager::dither(dither_kind kind)
{
    switch (kind) {
    case (WHITE_DITH): {
        wndithering.Dither(image1, image2);
        break;
    }
    case (BROWN_DITH): {
        bndithering.Dither(image1, image2);
        break;
    }
    case (VIOLET_DITH): {
        vndithering.Dither(image1, image2);
        break;
    }
    case (PINK_DITH): {
        pndithering.Dither(image1, image2);
        break;
    }
    case (BLUE_DITH): {
        blndithering.Dither(image1, image2);
        break;
    }
    default:
        break;
    };

}
