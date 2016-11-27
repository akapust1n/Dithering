#ifndef DITHERING_H
#define DITHERING_H
#include <QColor>
#include <QMap>
#include <QPixmap>
#include <memory>
class Dithering {
public:
    virtual void Dither(std::shared_ptr<QImage>& image1, std::shared_ptr<QImage>& image2) = 0;

protected:
    QRgb NewCOLOR(QColor pixel, int number);
    int width = 0;
    int height = 0;
};

class WhiteNoiseDithering : public Dithering {
public:
    virtual void Dither(std::shared_ptr<QImage>& image1, std::shared_ptr<QImage>& image2);
};
class BrownNoiseDithering : public Dithering {
public:
    virtual void Dither(std::shared_ptr<QImage>& image1, std::shared_ptr<QImage>& image2);
};
class VioletNoiseDithering : public Dithering {
public:
    virtual void Dither(std::shared_ptr<QImage>& image1, std::shared_ptr<QImage>& image2);
};
class PinkNoiseDithering : public Dithering {

public:
    virtual void Dither(std::shared_ptr<QImage>& image1, std::shared_ptr<QImage>& image2);
};
class BlueNoiseDithering : public Dithering {

public:
    virtual void Dither(std::shared_ptr<QImage>& image1, std::shared_ptr<QImage>& image2);
};
class FloydSDDithering : public Dithering {
public:
    virtual void Dither(std::shared_ptr<QImage>& image1, std::shared_ptr<QImage>& image2);
};

#endif // DITHERING_H
