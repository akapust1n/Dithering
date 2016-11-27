#ifndef COLORMAP_H
#define COLORMAP_H
#include <QImage>
#include <vector>
using namespace std;
struct mRgb {
    mRgb() {}
    mRgb(int _red, int _green, int _blue)
        : red(_red)
        , green(_green)
        , blue(_blue)
    {
    }
    double red = 0;
    double green = 0;
    double blue = 0;
    const mRgb operator-(mRgb obj);
    int getRed() { return static_cast<int>(red); }
    int getGreen() { return static_cast<int>(green); }
    int getBlue() { return static_cast<int>(blue); }
};

class ColorMap {
public:
    ColorMap(int _width, int _heidht);
    void updateValues(double koef, mRgb error, int j, int i);
    void initImage(QImage* image);
    mRgb getPixel(int j, int i);

private:
    int width;
    int height;
    vector<vector<double> > red;
    vector<vector<double> > blue;
    vector<vector<double> > green;
};

#endif // COLORMAP_H
