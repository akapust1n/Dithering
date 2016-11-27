#include "Dithering.h"
#include <QImage>
#include <DataManager.h>


QRgb Dithering::NewCOLOR(QColor pixel, int number)
{
    int move = number > 128 ? 1: 0;

    int rw = 51 * (((pixel.red()) + 25) / 51 + move);
    int gw = 51 * (((pixel.green()) + 25) / 51 + move);
    int bw = 51 * (((pixel.blue()) + 25) / 51 + move) ;
    rw = rw>204? 204:rw;
    gw = gw>204? 204:gw;
    bw = bw>204? 204:bw;


    QRgb _value;
    _value = qRgb(rw, gw, bw);
    return _value;
}
void WhiteNoiseDithering::Dither(std::shared_ptr<QImage> image1, std::shared_ptr<QImage> image2)
{
   image2.reset(new QImage(image1->width(), image1->height(),QImage::Format_RGB888));
    width = image2->width();
    height = image2->height();
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++){
            QRgb color = NewCOLOR(image1->pixelColor(j, i), rand()%256);
             image2->setPixel(j, i,color);
        }
    image2->save(DataManager::getImageName(DataManager::dithered_image));
}
