#ifndef DITHERMANAGER_H
#define DITHERMANAGER_H
#include <Dithering.h>
#include <QImage>

enum dither_kind {
    WHITE_DITH,
    BROWN_DITH,
    PINK_DITH,
    VIOLET_DITH,
    BLUE_DITH,
    FLOYDSD_DITH,
    NO_DITH,
    OTHER
};

class DitherManager {
public:
    void initImage(QImage* _image1);
    void dither(dither_kind kind);

private:
    WhiteNoiseDithering wndithering;
    BrownNoiseDithering bndithering;
    VioletNoiseDithering vndithering;
    PinkNoiseDithering pndithering;
    BlueNoiseDithering blndithering;
    FloydSDDithering floydSDdithering;

    QImage* image1;
    QImage* image2;
};

#endif // DITHERMANAGER_H
