#include "ColorMap.h"
#include <iostream>
const mRgb mRgb::operator-(mRgb obj)
{
    this->red -= obj.red;
    this->blue -= obj.blue;
    this->green -= obj.green;
    return *this;
}

ColorMap::ColorMap(int _width, int _heidht)
    : width(_width+1)
    , height(_heidht+1)
{
    for (int i = 0; i < width ; i++) {
        vector<double> temp(height , 0);
        vector<double> temp1(height,0);
        vector<double> temp2(height , 0);
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
    for (size_t i = 0; i < height-1; i++)
        for (size_t j = 0; j < width-1; j++) {
            auto color = image->pixel(j, i);
            //std::cout<<color.red()<<" "<<color.blue()<<std::endl;
            red[j][i] = qRed(color);
            blue[j][i] = qRed(color);
            green[j][i] = qRed(color);
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
