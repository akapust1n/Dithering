#include "ColorMap.h"
const mRgb mRgb::operator-(mRgb obj)
{
    this->red -= obj.red;
    this->blue -= obj.blue;
    this->green -= obj.green;
    return *this;
}

ColorMap::ColorMap(int _width, int _heidht)
    : width(_width)
    , height(_heidht)
{
    for (int i = 0; i < height + 1; i++) {
        vector<double> temp(width + 1, 0);
        vector<double> temp1(width + 1, 0);
        vector<double> temp2(width + 1, 0);
        red.push_back(temp);
        green.push_back(temp1);
        blue.push_back(temp2);
    }
}

void ColorMap::updateValues(double koef, mRgb error, int j, int i)
{
    red[j][i] += koef * error.red;
    green[j][i] += koef * error.green;
    blue[j][i] += koef * error.blue;
}

void ColorMap::initImage(QImage* image)
{
    for (size_t i = 0; i < height; i++)
        for (size_t j = 0; j < width; j++) {
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


}
