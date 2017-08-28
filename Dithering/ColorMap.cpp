#include "ColorMap.h"
#include <iostream>
//ещё алгоритмов дизеринга          ordered
const mRgb mRgb::operator-(mRgb obj)
{
    this->red -= obj.red;
    this->blue -= obj.blue;
    this->green -= obj.green;
    return *this;
}

ColorMap::ColorMap(int _width, int _heidht)
    : width(_width + 1)
    , height(_heidht + 1)
{
    for (int i = 0; i < width; i++) {
        vector<double> temp(height, 0);
        vector<double> temp1(height, 0);
        vector<double> temp2(height, 0);
        red.push_back(temp);
        green.push_back(temp1);
        blue.push_back(temp2);
    }
}

void ColorMap::updateValues(double koef, mRgb error, int j, int i)
{
    red[j][i] += koef * error.red;
    checkValue(red[j][i]);
    green[j][i] += koef * error.green;
    checkValue(green[j][i]);
    blue[j][i] += koef * error.blue;
    checkValue(blue[j][i]);
}

void ColorMap::initImage(QImage* image)
{
    for (size_t i = 0; i < height - 1; i++)
        for (size_t j = 0; j < width - 1; j++) {
            auto color = image->pixelColor(j, i);
            red[j][i] = color.red();
            blue[j][i] = color.blue();
            green[j][i] = color.green();
        }
}

mRgb ColorMap::getPixel(int j, int i)
{
    mRgb result;
    result.red = red[j][i];
    result.green = green[j][i];
    result.blue = blue[j][i];
    return result;
}

void ColorMap::checkValue(double& value)
{
    if (value > 255)
        value = 255;
    else if (value < 0)
        value = 0;
}
