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
    width = image2->width();
    height = image2->height();
    vector<vector<double> > Ired(width + 1, vector<double>(height + 1, 0));
    vector<vector<double> > Iblue(width + 1, vector<double>(height + 1, 0));
    vector<vector<double> > Igreen(width + 1, vector<double>(height + 1, 0));
    std::cout<<"begin dithering"<<std::endl;
    std::cout<<Ired.size()<<std::endl;

    for (size_t i = 0; i < height; i++)
        for (size_t j = 0; j < width; j++) {
            auto color = image1->pixelColor(j, i);
            Ired[j][i] = color.red();
            Iblue[j][i] = color.blue();
            Igreen[j][i] = color.green();
          //  std::cout<<"intro"<<std::endl;
        }
    std::cout<<"array created"<<std::endl;
    for (size_t i = 1; i < height; i++)
        for (size_t j = 1; j < width; j++) {
            QColor value = NewCOLOR(image1->pixelColor(j, i), Ired, Iblue, Igreen, 128, i, j);

            if (!map.contains(value.rgb())) {
                map.insert(value.rgb(), color_num);
                image2->setColor(color_num, value.rgb());
                color_num++;
                std::cout << "th" << map.value(value.rgb()) << "\n";
            }
            std::cout<<"MAP SIZE"<<map.size()<<std::endl;

            image2->setPixel(j, i, map.value(value.rgb()));
        }
    std::cout<<"image created"<<std::endl;

    image2->save(DataManager::getImageName(BLUE_DITH));
    delete image2;
    map.clear();

    //
    //            if( I(pixel) > Threshold )
    //                  {
    //                      I(pixel) = Белый;
    //                      Error = I(pixel) - Белый;
    //                  }
    //                  else
    //                  {
    //                      I(pixel) = Черный;
    //                      Error = I(pixel) - Черный;
    //                  }
    //                  I(pixel.right)+= 7/16 * Error;
    //                  I(pixel.down_right)+= 1/16 * Error;
    //                  I(pixel.down)+= 5/16 * Error;
    //                  I(pixel.down_left)+= 3/16 * Error;
    //        }
}

QRgb FloydSDDithering::NewCOLOR(QColor pixel, auto& red, auto& green, auto& blue, int value, size_t i, size_t j)
{
    int error1 = 0;
    int error2 = 0;
    int error3 = 0;

    if (red[j][i] > value) {
        red[j][i] = 255;
        error1 = pixel.red() - 255;
    }
    if (green[j][i] > value) {
        green[j][i] = 255;
        error2 = pixel.green() - 255;
    }
    if (blue[j][i] > value) {
        blue[j][i] = 255;
        error3 = pixel.blue() - 255;
    }
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
    return _value;
}
