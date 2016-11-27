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
        red_noise,
        violet_noise
    };
    void Dither(kind_dither kindDither);
    void initImages(std::shared_ptr<QImage> _image1,std::shared_ptr<QImage> _image2);
private:
    WhiteNoiseDithering whiteNoiseDithering;
    std::shared_ptr<QImage> image1;
    std::shared_ptr<QImage> image2;
};

#endif // DITHERMANAGER_H
