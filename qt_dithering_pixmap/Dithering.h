#ifndef DITHERING_H
#define DITHERING_H
#include <QColor>
#include <QPixmap>
class Dithering {
public:
    virtual void Dither(QImage& image1, QImage& image2) ;

private:
    virtual void Compare(QColor  pixel, int number) ;
};
class WhiteNoiseDithering : public Dithering {
public:
    virtual void Dither(QImage& image1, QImage& image2);
private:
    virtual QColor Compare(QColor pixel, int number);
};
class BrownNoiseDithering : public Dithering {
public:
    virtual void Dither(QImage& image1, QImage& image2);
private:
    virtual QColor Compare(QColor pixel, int number);
};
#endif // DITHERING_H
