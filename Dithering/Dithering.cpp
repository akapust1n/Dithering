#include "Dithering.h"
#include <ColorMap.h>
#include <DataManager.h>
#include <DitherManager.h>
#include <QImage>
#include <ctime>
#include <iostream>

QRgb Dithering::NewCOLOR(QColor pixel, int number = 0)
{
    int move = number > 128 ? 1 : 0;

    int rw = 51 * (((pixel.red()) + 25) / 51 + move);
    int gw = 51 * (((pixel.green()) + 25) / 51 + move);
    int bw = 51 * (((pixel.blue()) + 25) / 51 + move);
    rw = rw > 255 ? 255 : rw; //max value for web-safe palette
    gw = gw > 255 ? 255 : gw;
    bw = bw > 255 ? 255 : bw;

    QRgb _value;
    _value = qRgb(rw, gw, bw);
    return _value;
}
void WhiteNoiseDithering::Dither(std::shared_ptr<QImage>& image1, std::shared_ptr<QImage>& image2)
{
    image2.reset(new QImage(image1->width(), image1->height(), QImage::Format_RGB888));
    width = image2->width();
    height = image2->height();
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            QRgb color = NewCOLOR(image1->pixel(j, i), rand() % 256);
            image2->setPixel(j, i, color);
        }
    image2->save(DataManager::getImageName(DataManager::dithered_image));
    image2->save(DitherManager::getImageName(DitherManager::white_noise));
}

void BrownNoiseDithering::Dither(std::shared_ptr<QImage>& image1, std::shared_ptr<QImage>& image2)
{
    image2.reset(new QImage(image1->width(), image1->height(), QImage::Format_RGB888));
    width = image2->width();
    height = image2->height();
    int number[3];
    srand(time(0));

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            number[0] = rand() % 256;
            number[1] = rand() % 256;
            number[2] = 0.5 * (number[0] + number[1]);
            if (number[2] > 255)
                number[2] = 255;
            QRgb color = NewCOLOR(image1->pixel(j, i), number[2]);
            image2->setPixel(j, i, color);
        }
    image2->save(DataManager::getImageName(DataManager::dithered_image));
    image2->save(DitherManager::getImageName(DitherManager::brown_noise));
}

void VioletNoiseDithering::Dither(std::shared_ptr<QImage>& image1, std::shared_ptr<QImage>& image2)
{
    image2.reset(new QImage(image1->width(), image1->height(), QImage::Format_RGB888));
    width = image2->width();
    height = image2->height();
    int number[3];
    srand(time(0));

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            number[0] = rand() % 256;
            number[1] = rand() % 256;
            number[2] = 0.5 * (number[0] - number[1]);

            if (number[2] < 0)
                number[2] = -number[2];
            if (number[2] > 255)
                number[2] = 255;
            QRgb color = NewCOLOR(image1->pixel(j, i), number[2]);
            image2->setPixel(j, i, color);
        }
    image2->save(DataManager::getImageName(DataManager::dithered_image));
    image2->save(DitherManager::getImageName(DitherManager::violet_noise));
}

void BlueNoiseDithering::Dither(std::shared_ptr<QImage>& image1, std::shared_ptr<QImage>& image2)
{
    image2.reset(new QImage(image1->width(), image1->height(), QImage::Format_RGB888));
    width = image2->width();
    height = image2->height();
    int number[3];
    srand(time(0));

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            number[0] = rand() % 256;
            number[1] = rand() % 256;
            number[2] = 0.7 * (number[0] - number[1]);
            if (number[2] < 0)
                number[2] = -number[2];
            if (number[2] > 255)
                number[2] = 255;
            QRgb color = NewCOLOR(image1->pixel(j, i), number[2]);
            image2->setPixel(j, i, color);
        }
    image2->save(DataManager::getImageName(DataManager::dithered_image));
    image2->save(DitherManager::getImageName(DitherManager::blue_noise));
}

void PinkNoiseDithering::Dither(std::shared_ptr<QImage>& image1, std::shared_ptr<QImage>& image2)
{
    image2.reset(new QImage(image1->width(), image1->height(), QImage::Format_RGB888));
    width = image2->width();
    height = image2->height();
    int number[3];
    srand(time(0));

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {
            number[0] = rand() % 256;
            number[1] = rand() % 256;
            number[2] = 0.3 * (number[0] + number[1]);
            if (number[2] > 255)
                number[2] = 255;
            QRgb color = NewCOLOR(image1->pixel(j, i), number[2]);
            image2->setPixel(j, i, color);
        }
    image2->save(DataManager::getImageName(DataManager::dithered_image));
    image2->save(DitherManager::getImageName(DitherManager::pink_noise));
}

void FloydSDDithering::Dither(std::shared_ptr<QImage>& image1, std::shared_ptr<QImage>& image2)
{
    image2.reset(new QImage(image1->width(), image1->height(), QImage::Format_RGB888));
    width = image2->width();
    height = image2->height();
    ColorMap colorMap(width, height);
    colorMap.initImage(image1.get());
    for (int i = 1; i < height; i++)
        for (int j = 1; j < width; j++) {
            mRgb oldPixel = colorMap.getPixel(j, i);

            QColor newPixel(oldPixel.getRed(), oldPixel.getGreen(), oldPixel.getBlue());
            QColor value = NewCOLOR(newPixel);
            mRgb error(value.red(), value.green(), value.blue());
            error = oldPixel - error;
            colorMap.updateValues(7.0 / 16, error, j + 1, i);
            colorMap.updateValues(1.0 / 16, error, j + 1, i + 1);
            colorMap.updateValues(5.0 / 16, error, j - 1, i);
            colorMap.updateValues(3.0 / 16, error, j, i + 1);

            image2->setPixelColor(j, i, value);
        }
    image2->save(DataManager::getImageName(DataManager::dithered_image));
    image2->save(DitherManager::getImageName(DitherManager::floyd_sd));
}


void FalseFloydSDDithering::Dither(std::shared_ptr<QImage>& image1, std::shared_ptr<QImage>& image2)
{
    image2.reset(new QImage(image1->width(), image1->height(), QImage::Format_RGB888));
    width = image2->width();
    height = image2->height();
    ColorMap colorMap(width, height);
    colorMap.initImage(image1.get());
    for (int i = height - 1; i > 0; i--)
        for (int j = width - 1; j > 0; j--) {
            mRgb oldPixel = colorMap.getPixel(j, i);

            QColor newPixel(oldPixel.getRed(), oldPixel.getGreen(), oldPixel.getBlue());
            QColor value = NewCOLOR(newPixel);
            mRgb error(value.red(), value.green(), value.blue());
            error = oldPixel - error;
            colorMap.updateValues(3.0 / 8, error, j - 1, i);
            colorMap.updateValues(2.0 / 8, error, j - 1, i - 1);
            colorMap.updateValues(3.0 / 8, error, j, i - 1);

            image2->setPixelColor(j, i, value);
        }
    image2->save(DataManager::getImageName(DataManager::dithered_image));
    image2->save(DitherManager::getImageName(DitherManager::false_floyd_sd));
}

void JJNDithering::Dither(std::shared_ptr<QImage> &image1, std::shared_ptr<QImage> &image2)
{
    image2.reset(new QImage(image1->width(), image1->height(), QImage::Format_RGB888));
    width = image2->width();
    height = image2->height();
    ColorMap colorMap(width+2, height+2);
    colorMap.initImage(image1.get());
    for (int i = 2; i < height; i++)
        for (int j = 0; j < width; j++) {
            mRgb oldPixel = colorMap.getPixel(j, i);

            QColor newPixel(oldPixel.getRed(), oldPixel.getGreen(), oldPixel.getBlue());
            QColor value = NewCOLOR(newPixel);
            mRgb error(value.red(), value.green(), value.blue());
            error = oldPixel - error;
            colorMap.updateValues(3.0 / 48, error, j + 1, i+2);
            colorMap.updateValues(5.0 / 48, error, j + 1, i+1);
            colorMap.updateValues(7.0 / 48, error, j + 1, i);
            colorMap.updateValues(5.0 / 48, error, j + 1, i-1);
            colorMap.updateValues(3.0 / 48, error, j + 1, i-2);
            colorMap.updateValues(1.0 / 48, error, j + 2, i+2);
            colorMap.updateValues(3.0 / 48, error, j + 2, i+1);
            colorMap.updateValues(5.0 / 48, error, j + 2, i);
            colorMap.updateValues(3.0 / 48, error, j + 2, i-1);
            colorMap.updateValues(1.0 / 48, error, j + 2, i-2);
            colorMap.updateValues(7.0 / 48, error, j , i+1);
            colorMap.updateValues(5.0 / 48, error, j, i+2);

            image2->setPixelColor(j, i, value);
        }
    image2->save(DataManager::getImageName(DataManager::dithered_image));
    image2->save(DitherManager::getImageName(DitherManager::jjn));

}
