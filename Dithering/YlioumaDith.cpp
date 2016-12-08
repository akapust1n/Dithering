#include "DitherManager.h"
#include <DataManager.h>
#include <YlioumaDith.h>
#include <cmath>
#include <iostream>
constexpr double Yliluoma1::map1[64];
//constexpr unsigned Yliluoma1::pal[16];

Yliluoma1::Yliluoma1()
{
    int index = 0;
    for (int r = 255; r >= 0; r -= 51)
        for (int g = 255; g >= 0; g -= 51)
            for (int b = 255; b >= 0; b -= 51) {
                unsigned rgb = ((r & 0x0ff) << 16) | ((g & 0x0ff) << 8) | (b & 0x0ff);
                pal[index++] = rgb;
            }
    std::cout << index << "INDEX" << std::endl;
}

int Yliluoma1::Dither(std::shared_ptr<QImage>& image1, std::shared_ptr<QImage>& image2)
{
    std::cout << "START" << std::endl;
    image2.reset(new QImage(image1->width(), image1->height(), QImage::Format_RGB888));
    width = image2->width();
    height = image2->height();
    start = std::chrono::system_clock::now();

#pragma omp parallel for
    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            //unsigned color = gdImageGetTrueColorPixel(srcim, x, y);
            QColor temp = image1->pixelColor(x, y);

            unsigned color = qColorToint(temp);
          //  std::cout << "before " << color << std::endl;
            MixingPlan plan = DeviseBestMixingPlan(color);
            if (plan.ratio == 4.0) // Tri-tone or quad-tone dithering
            {
                QColor color = rgbToQColor(plan.colors[((y & 1) * 2 + (x & 1))]);
                image2->setPixelColor(x, y, color);
            } else {
                double map_value = Yliluoma1::map1[(x & 7) + ((y & 7) << 3)];
                QColor color;
               // std::cout << plan.colors[map_value < plan.ratio ? 1 : 0] << std::endl;
                color = rgbToQColor(plan.colors[map_value < plan.ratio ? 1 : 0]);
                image2->setPixelColor(x, y, color);
                // std::cout<<"BLACK"<<std::endl;
            }
        }
        std::cout << y << std::endl;
    }
    end = std::chrono::system_clock::now();
    elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>
                                 (end-start).count();
    std::cout << "SAVE" << std::endl;
    image2->save(DataManager::getImageName(DataManager::dithered_image));
    image2->save(DitherManager::getImageName(DitherManager::yliluoma1));
    return  elapsed_time;
}

int Yliluoma1::Dither(std::shared_ptr<QImage> &image1)
{
//to slow for implement
    return 0;
}

double Yliluoma1::ColorCompare(int r1, int g1, int b1, int r2, int g2, int b2)
{
    double luma1 = (r1 * 299 + g1 * 587 + b1 * 114) / (255.0 * 1000);
    double luma2 = (r2 * 299 + g2 * 587 + b2 * 114) / (255.0 * 1000);
    double lumadiff = luma1 - luma2;
    double diffR = (r1 - r2) / 255.0, diffG = (g1 - g2) / 255.0, diffB = (b1 - b2) / 255.0;
    return (diffR * diffR * 0.299 + diffG * diffG * 0.587 + diffB * diffB * 0.114) * 0.75
        + lumadiff * lumadiff;
}

double Yliluoma1::EvaluateMixingError(int r, int g, int b, int r0, int g0, int b0, int r1, int g1, int b1, int r2, int g2, int b2, double ratio)
{
    return ColorCompare(r, g, b, r0, g0, b0)
        + ColorCompare(r1, g1, b1, r2, g2, b2) * 0.1 * (fabs(ratio - 0.5) + 0.5);
}

Yliluoma1::MixingPlan Yliluoma1::DeviseBestMixingPlan(unsigned color)
{
    const unsigned r = color >> 16, g = (color >> 8) & 0xFF, b = color & 0xFF;
    MixingPlan result = { { 0, 0 }, 0.5 };
    double least_penalty = 1e99;
    for (unsigned index1 = 0; index1 < 216; ++index1)
        for (unsigned index2 = index1; index2 < 216; ++index2)
        //for(int ratio=0; ratio<64; ++ratio)
        {
            // Determine the two component colors
            unsigned color1 = pal[index1], color2 = pal[index2];
            unsigned r1 = color1 >> 16, g1 = (color1 >> 8) & 0xFF, b1 = color1 & 0xFF;
            unsigned r2 = color2 >> 16, g2 = (color2 >> 8) & 0xFF, b2 = color2 & 0xFF;
            int ratio = 32;
            if (color1 != color2) {
                // Determine the ratio of mixing for each channel.
                //   solve(r1 + ratio*(r2-r1)/64 = r, ratio)
                // Take a weighed average of these three ratios according to the
                // perceived luminosity of each channel (according to CCIR 601).
                ratio = ((r2 != r1 ? 299 * 64 * int(r - r1) / int(r2 - r1) : 0)
                            + (g2 != g1 ? 587 * 64 * int(g - g1) / int(g2 - g1) : 0)
                            + (b1 != b2 ? 114 * 64 * int(b - b1) / int(b2 - b1) : 0))
                    / ((r2 != r1 ? 299 : 0)
                            + (g2 != g1 ? 587 : 0)
                            + (b2 != b1 ? 114 : 0));
                if (ratio < 0)
                    ratio = 0;
                else if (ratio > 63)
                    ratio = 63;
            }
            // Determine what mixing them in this proportion will produce
            unsigned r0 = r1 + ratio * int(r2 - r1) / 64;
            unsigned g0 = g1 + ratio * int(g2 - g1) / 64;
            unsigned b0 = b1 + ratio * int(b2 - b1) / 64;
            double penalty = EvaluateMixingError(
                r, g, b, r0, g0, b0, r1, g1, b1, r2, g2, b2,
                ratio / double(64));
            if (penalty < least_penalty) {
                least_penalty = penalty;
                result.colors[0] = pal[index1];
                result.colors[1] = pal[index2];
                result.ratio = ratio / double(64);
            }
            if (index1 != index2)
                for (unsigned index3 = 0; index3 < 216; ++index3) {
                    if (index3 == index2 || index3 == index1)
                        continue;
                    // 50% index3, 25% index2, 25% index1
                    unsigned color3 = pal[index3];
                    unsigned r3 = color3 >> 16, g3 = (color3 >> 8) & 0xFF, b3 = color3 & 0xFF;
                    r0 = (r1 + r2 + r3 * 2) / 4;
                    g0 = (g1 + g2 + g3 * 2) / 4;
                    b0 = (b1 + b2 + b3 * 2) / 4;
                    penalty = ColorCompare(r, g, b, r0, g0, b0)
                        + ColorCompare(r1, g1, b1, r2, g2, b2) * 0.025
                        + ColorCompare((r1 + g1) / 2, (g1 + g2) / 2, (b1 + b2) / 2, r3, g3, b3) * 0.025;
                    if (penalty < least_penalty) {
                        least_penalty = penalty;
                        result.colors[0] = pal[index3]; // (0,0) index3 occurs twice
                        result.colors[1] = pal[index1]; // (0,1)
                        result.colors[2] = pal[index2]; // (1,0)
                        result.colors[3] = pal[index3]; // (1,1)
                        result.ratio = 4.0;
                    }
                }
        }
    return result;
}

QColor Yliluoma1::rgbToQColor(unsigned color1)
{
    unsigned r1 = color1 >> 16, g1 = (color1 >> 8) & 0xFF, b1 = color1 & 0xFF;
    //  std::cout<<r1<<" "<<g1<<" "<<b1<<std::endl;

    QColor result(r1, g1, b1);
    return result;
}

unsigned Yliluoma1::qColorToint(QColor& color)
{
    unsigned r = color.red();
    unsigned g = color.green();
    unsigned b = color.blue();
    // std::cout<<r<<" "<<g<<" "<<b<<std::endl;

    unsigned rgb = ((r & 0x0ff) << 16) | ((g & 0x0ff) << 8) | (b & 0x0ff);
    //  std::cout << rgb << std::endl;
    return rgb;
}
