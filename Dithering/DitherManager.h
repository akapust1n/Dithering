#ifndef DITHERMANAGER_H
#define DITHERMANAGER_H

#include <Dithering.h>
#include <memory>

class DitherManager {
public:
    enum kind_dither {
        white_noise,
        blue_noise,
        brown_noise,
        pink_noise,
        violet_noise,
        floyd_sd
    };
    void Dither(kind_dither kindDither);
    void initImages(std::shared_ptr<QImage> &_image1, std::shared_ptr<QImage> &_image2);
    static  QString getImageName(kind_dither kindDither);
    std::shared_ptr<QImage> &getImage();

private:
    WhiteNoiseDithering whiteNoiseDithering;
    BlueNoiseDithering blueNoiseDithering;
    PinkNoiseDithering pinkNoiseDithering;
    BrownNoiseDithering brownNoiseDithering;
    VioletNoiseDithering violetNoiseDithering;
    FloydSDDithering floydSDDithering;
    std::shared_ptr<QImage> image1;
    std::shared_ptr<QImage> image2;
};

#endif // DITHERMANAGER_H
