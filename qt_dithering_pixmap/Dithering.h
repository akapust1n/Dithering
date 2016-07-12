#ifndef DITHERING_H
#define DITHERING_H
#include <QColor>
#include <QPixmap>
#include <QSet>
class Dithering {
public:
    QSet<int> set;
    virtual void Dither(QImage& image1, QImage& image2) = 0;
private:
    QRgb NewCOLOR(QColor pixel, int number);
    int addColorToTable()
};
class WhiteNoiseDithering : public Dithering {
public:
    virtual void Dither(QImage& image1, QImage& image2);

private:
    // virtual QColor NewCOLOR(QColor pixel, int number);
};/*
class BrownNoiseDithering : public Dithering {
public:
    virtual void Dither(QImage& image1, QImage& image2);

private:
    //virtual QColor NewCOLOR(QColor pixel, int number);
};
*/
#endif // DITHERING_H
