#ifndef DITHERING_H
#define DITHERING_H
#include <QColor>
#include <QMap>
#include <QPixmap>
#include <stdlib.h>
#include <time.h>
#include <array>

class Dithering {
public:
    virtual void Dither(QImage*& image1, QImage*& image2) = 0;

protected:
    QRgb NewCOLOR(QColor pixel, int number);
    QMap<QRgb, int> map;
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
    int key = 0;
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
class FloydSDDithering : public Dithering {
public:
    virtual void Dither(QImage*& image1, QImage*& image2);
private:
    QRgb NewCOLOR(QColor pixel);


};

#endif // DITHERING_H
