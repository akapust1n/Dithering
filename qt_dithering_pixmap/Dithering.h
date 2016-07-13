#ifndef DITHERING_H
#define DITHERING_H
#include <QColor>
#include <QPixmap>
#include <QMap>
class Dithering {
public:
    QMap<QRgb,int> map;
    virtual void Dither(QImage& image1, QImage& image2) = 0;
    protected:
    QRgb NewCOLOR(QColor pixel, int number);
    //int addColorToTable()
};
class WhiteNoiseDithering : public Dithering {
public:
    virtual void Dither(QImage& image1, QImage& image2);

private:
    // virtual QColor NewCOLOR(QColor pixel, int number);
};
class BrownNoiseDithering : public Dithering {
public:
    virtual void Dither(QImage& image1, QImage& image2);

private:
    //virtual QColor NewCOLOR(QColor pixel, int number);
};
class PinkNoiseDithering : public Dithering {
public:
    virtual void Dither(QImage& image1, QImage& image2);

private:
    //virtual QColor NewCOLOR(QColor pixel, int number);
};

#endif // DITHERING_H
