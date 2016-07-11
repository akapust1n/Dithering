#ifndef DITHERING_H
#define DITHERING_H
#include <QPixmap>
class Dithering
{
public:
    virtual void Dither(QPixmap &image1,QPixmap &image2);
};

#endif // DITHERING_H
