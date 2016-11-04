#ifndef DITHERING_H
#define DITHERING_H
#include <QColor>
#include <QPixmap>
#include <QMap>
#include <time.h>
#include <stdlib.h>

class Dithering {
public:
    virtual void Dither(QImage*& image1, QImage*& image2) = 0;
protected:
    QRgb NewCOLOR(QColor pixel, int number);
    QMap<QRgb,int> map;
    int width;
    int height;
    int color_num = 0;


};
class WhiteNoiseDithering : public Dithering {
public:
    virtual void Dither(QImage*& image1, QImage*& image2);

};
class BrownNoiseDithering : public Dithering {
public:
    int key= 0;
    virtual void Dither(QImage*& image1, QImage*& image2);

};
class VioletNoiseDithering : public Dithering {
public:
    virtual void Dither(QImage*& image1, QImage*& image2);
};
class PinkNoiseDithering : public Dithering {

public:
    virtual void Dither(QImage*& image1, QImage*& image2);
};
class BlueNoiseDithering : public Dithering {

public:
    virtual void Dither(QImage*& image1, QImage*& image2);
};
/*
class BlueNoiseDithering : public Dithering {

public:
    virtual void Dither(QImage*& image1, QImage*& image2);
};
*/


#endif // DITHERING_H
