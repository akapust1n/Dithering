#ifndef DITHERMANAGER_H
#define DITHERMANAGER_H
#include <QImage>
#include <Dithering.h>

enum dither_kind {
    WHITE_DITH, BROWN_DITH,PINK_DITH,VIOLET_DITH,BLUE_DITH
};

class DitherManager
{
public:
    void initImage(QImage* _image1);
    void dither(dither_kind kind);
private:
    WhiteNoiseDithering wndithering;
    BrownNoiseDithering bndithering;
    VioletNoiseDithering vndithering;
    PinkNoiseDithering  pndithering;
    BlueNoiseDithering  blndithering;

    QImage *image1;
    QImage *image2;
};

#endif // DITHERMANAGER_H
