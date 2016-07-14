#include <MainManager.h>
void MainManager::loadFile(QString& fname)
{
    image1 = dataread.openImage(fname);

}
void MainManager::dither(dither_kind kind)
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
