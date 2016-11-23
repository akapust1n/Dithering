#include <DataManager.h>
#include <Dithering.h>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>

QRgb Dithering::NewCOLOR(QColor pixel, int number)
{
    int red, blue, green;

    if (pixel.blue() > number)
        blue = 255;
    else
        blue = 0;
    if (pixel.red() > number)
        red = 255;
    else
        red = 0;
    if (pixel.green() > number)
        green = 255;
    else
        green = 0;
    QRgb value;
    value = qRgb(red, green, blue);

    return value;
}
//----------------------------------белый шум-------------------------------------
void WhiteNoiseDithering::Dither(QImage*& image1, QImage*& image2)
{
    //std::cout << "color count" << image1->colorCount() << std::endl;
    image2 = new QImage;
    *image2 = image1->copy();
    std::cout << "color count" << image2->colorCount() << std::endl;
    int width = image2->width();
    int height = image2->height();
    int number = 0;
    int color_num = 0;
    srand(time(0));
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {

            number = rand() % 256;
            QRgb value = NewCOLOR(image1->pixelColor(j, i), number);
            if (!map.contains(value)) {
                map.insert(value, color_num);
                image2->setColor(color_num, value);
                color_num++;
                std::cout << "th" << map.value(value) << "\n";
            }
            image2->setPixel(j, i, map.value(value));
        }
    image2->save(DataManager::getImageName(WHITE_DITH));
    delete image2;
    map.clear();
}

//---------------------------------коричневый шум--------------

void BrownNoiseDithering::Dither(QImage*& image1, QImage*& image2)

{
    image2 = new QImage;
    *image2 = image1->copy();
    int width = image2->width();
    int height = image2->height();
    int color_num = 0;
    int number[3];
    srand(time(0));
    number[0] = rand() % 256;
    number[1] = rand() % 256;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {

            number[2] = 0.5 * (number[0] + number[1]);
            if (number[2] > 255)
                number[2] = 255;
            QRgb value = NewCOLOR(image1->pixelColor(j, i), number[2]);
            if (!map.contains(value)) {
                map.insert(value, color_num);
                image2->setColor(color_num, value);
                color_num++;
                std::cout << "th" << map.value(value) << "\n";
            }
            image2->setPixel(j, i, map.value(value));
            number[1] = number[0];
            number[0] = rand() % 256;
        }

    image2->save(DataManager::getImageName(BROWN_DITH));

    key++;
    delete image2;
    map.clear();
}
//------------------------------------фиолетовый шум------------------
void VioletNoiseDithering::Dither(QImage*& image1, QImage*& image2)
{
    image2 = new QImage;
    *image2 = image1->copy();
    int width = image2->width();
    int height = image2->height();
    int color_num = 0;
    int number[3];
    srand(time(0));
    number[0] = rand() % 256;
    number[1] = rand() % 256;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {

            number[2] = 0.5 * (number[0] - number[1]);
            if (number[2] < 0)
                number[2] = -number[2];
            if (number[2] > 255)
                number[2] = 255;
            QRgb value = NewCOLOR(image1->pixelColor(j, i), number[2]);
            if (!map.contains(value)) {
                map.insert(value, color_num);
                image2->setColor(color_num, value);
                color_num++;
                std::cout << "th" << map.value(value) << "\n";
            }
            image2->setPixel(j, i, map.value(value));
            number[1] = number[0];
            number[0] = rand() % 256;
        }
    image2->save(DataManager::getImageName(VIOLET_DITH));
    delete image2;
    map.clear();
}

//-----------------------------розовый шум---------------------
void PinkNoiseDithering::Dither(QImage*& image1, QImage*& image2)

{
    image2 = new QImage;
    *image2 = image1->copy();
    int width = image2->width();
    int height = image2->height();
    int color_num = 0;
    int number[3];
    number[0] = rand() % 256;
    number[1] = rand() % 256;
    srand(time(0));
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {

            number[2] = 0.3 * (number[0] + number[1]);
            if (number[2] > 255)
                number[2] = 255;
            QRgb value = NewCOLOR(image1->pixelColor(j, i), number[2]);
            if (!map.contains(value)) {
                map.insert(value, color_num);
                image2->setColor(color_num, value);
                color_num++;
                std::cout << "th" << map.value(value) << "\n";
            }
            image2->setPixel(j, i, map.value(value));
            number[1] = number[0];
            number[0] = rand() % 256;
        }

    image2->save(DataManager::getImageName(PINK_DITH));
    delete image2;
    map.clear();
}
//--------------------------голубой шум-------------------------------------
void BlueNoiseDithering::Dither(QImage*& image1, QImage*& image2)
{
    image2 = new QImage;
    *image2 = image1->copy();
    width = image2->width();
    height = image2->height();
    int number[3];
    srand(time(0));
    number[0] = rand() % 256;
    number[1] = rand() % 256;
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++) {

            number[2] = 0.7 * (number[0] - number[1]);
            if (number[2] < 0)
                number[2] = -number[2];
            if (number[2] > 255)
                number[2] = 255;
            QRgb value = NewCOLOR(image1->pixelColor(j, i), number[2]);
            if (!map.contains(value)) {
                map.insert(value, color_num);
                image2->setColor(color_num, value);
                color_num++;
                std::cout << "th" << map.value(value) << "\n";
            }
            image2->setPixel(j, i, map.value(value));
            number[1] = number[0];
            number[0] = rand() % 256;
        }
    image2->save(DataManager::getImageName(BLUE_DITH));
    delete image2;
    map.clear();
}

void FloydSDDithering::Dither(QImage*& image1, QImage*& image2)
{
    image2 = new QImage;
    *image2 = image1->copy();
    width = image2->width() - 1;
    height = image2->height() - 1;
    vector<vector<double> > red(width + 1, vector<double>(height + 1, 0));
    vector<vector<double> > blue(width + 1, vector<double>(height + 1, 0));
    vector<vector<double> > green(width + 1, vector<double>(height + 1, 0));
    for (size_t i = 0; i < height; i++)
        for (size_t j = 0; j < width; j++) {
            auto color = image1->pixelColor(j, i);
            red[j][i] = color.red();
            blue[j][i] = color.blue();
            green[j][i] = color.green();
            //  std::cout<<"intro"<<std::endl;
        }

    for (int i = 1; i < height; i++)
        for (int j = 1; j < width; j++) {
            int oldpixelR = red[j][i];
            int oldpixelG = green[j][i];
            int oldpixelB = blue[j][i];
            QColor oldpixel(oldpixelR,oldpixelG,oldpixelB);
            QColor value = NewCOLOR(oldpixel);
            if (!map.contains(value.rgb())) {
                map.insert(value.rgb(), color_num);
                image2->setColor(color_num, value.rgb());
                color_num++;
                //   std::cout << "th" << map.value(value) << "\n";
            }
            int error1 = oldpixelR-value.red();
            int error2 = oldpixelR-value.green();
            int error3 = oldpixelR-value.blue();


            red[j + 1][i] += 7 / 16 * error1;
            green[j + 1][i] += 7 / 16 * error2;
            blue[j + 1][i] += 7 / 16 * error3;

            red[j + 1][i + 1] += 1 / 16 * error1;
            green[j + 1][i + 1] += 1 / 16 * error2;
            blue[j + 1][i + 1] += 1 / 16 * error3;

            red[j][i + 1] += 5 / 16 * error1;
            green[j][i + 1] += 5 / 16 * error2;
            blue[j][i + 1] += 5 / 16 * error3;

            red[j - 1][i] += 3 / 16 * error1;
            green[j - 1][i] += 3 / 16 * error2;
            blue[j - 1][i] += 3 / 16 * error3;

            QRgb _value;
            value = qRgb(red[j][i], green[j][i], blue[j][i]);
            image2->setPixel(j, i, map.value(value.rgb()));
        }
    std::cout << "image created" << std::endl;

    image2->save(DataManager::getImageName(FLOYDSD_DITH));
    delete image2;
    map.clear();;
}

QRgb FloydSDDithering::NewCOLOR(QColor pixel)
{
    int rw = 51 * ((pixel.red()) + 25) / 51;
    int gw = 51 * ((pixel.green()) + 25) / 51;
    int bw = 51 * ((pixel.blue()) + 25) / 51;

    QRgb _value;
    _value = qRgb(rw, gw, bw);
    return _value;
}
