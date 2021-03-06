#ifndef DITHERING_H
#define DITHERING_H
#include <QColor>
#include <QMap>
#include <QPixmap>
#include <chrono>
#include <memory>
class Dithering {
public:
    virtual int Dither(std::shared_ptr<QImage>& image1, std::shared_ptr<QImage>& image2) = 0;
    virtual int Dither(std::shared_ptr<QImage>& image1) = 0;

protected:
    std::chrono::time_point<std::chrono::system_clock>
        start, end;
    QColor NewCOLOR(QColor pixel, int number);
    int width = 0;
    int height = 0;
    long elapsed_time = 0;
};

class WhiteNoiseDithering : public Dithering {
public:
    virtual int Dither(std::shared_ptr<QImage>& image1, std::shared_ptr<QImage>& image2);
    virtual int Dither(std::shared_ptr<QImage>& image1);
};
class BrownNoiseDithering : public Dithering {
public:
    virtual int Dither(std::shared_ptr<QImage>& image1, std::shared_ptr<QImage>& image2);
    virtual int Dither(std::shared_ptr<QImage>& image1);
};
class VioletNoiseDithering : public Dithering {
public:
    virtual int Dither(std::shared_ptr<QImage>& image1, std::shared_ptr<QImage>& image2);
    virtual int Dither(std::shared_ptr<QImage>& image1);
};
class PinkNoiseDithering : public Dithering {

public:
    virtual int Dither(std::shared_ptr<QImage>& image1, std::shared_ptr<QImage>& image2);
    virtual int Dither(std::shared_ptr<QImage>& image1);
};
class BlueNoiseDithering : public Dithering {

public:
    virtual int Dither(std::shared_ptr<QImage>& image1, std::shared_ptr<QImage>& image2);
    virtual int Dither(std::shared_ptr<QImage>& image1);
};
class FloydSDDithering : public Dithering {
public:
    virtual int Dither(std::shared_ptr<QImage>& image1, std::shared_ptr<QImage>& image2);
    virtual int Dither(std::shared_ptr<QImage>& image1);
};
class FalseFloydSDDithering : public Dithering {
public:
    virtual int Dither(std::shared_ptr<QImage>& image1, std::shared_ptr<QImage>& image2);
    virtual int Dither(std::shared_ptr<QImage>& image1);
};
class JJNDithering : public Dithering {
public:
    virtual int Dither(std::shared_ptr<QImage>& image1, std::shared_ptr<QImage>& image2);
    virtual int Dither(std::shared_ptr<QImage>& image1);
};

#endif // DITHERING_H
