#include <MainManager.h>
void MainManager::loadFile(QString& fname)
{
    image1 = dataread.openImage(fname);
}
void MainManager::dither(dither_kind kind)
{
    switch (kind) {
    case (WHITE_DITH):
        wndithering.Dither(image1, image2);
        break;
    case (BROWN_DITH):
        //bndothering.Dither(image1,image2);
        break;
    default : break;
    };
}
