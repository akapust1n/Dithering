#include "Metrics.h"
#include <cmath>
#include <iostream>

double Metrics::getBitDepth(int depth)
{
    return (pow(2, depth) - 1);
}

double PSNR::getValue(std::shared_ptr<QImage> image1, std::shared_ptr<QImage> image2)
{
    double result = calculate(image1->depth(), sqrt(getMSE(image1, image2)));
    return result;
}

double PSNR::getMSE(std::shared_ptr<QImage> image1, std::shared_ptr<QImage> image2)
{
    int b1 = 0, g1 = 0, b2 = 0, g2 = 0, r1 = 0, r2 = 0;
    double sum = 0;
    int width = image1->width() - 1;
    int height = image1->height() - 1;
    for (int x = 0; x <= width; x++) {
        for (int y = 0; y <= height; y++) {
//            if(!image2.get()) std::cout<<"null image"<<std::endl;
//            std::cout<<x<<" "<<y<<std::endl;
            QColor pixel1 = image1->pixel(x, y);
            QColor pixel2 = image2->pixel(x, y);

            b1 = pixel1.blue();
            g1 = pixel1.green();
            r1 = pixel1.red();

            b2 = pixel2.blue();
            g2 = pixel2.green();
            r2 = pixel2.red();
            sum += pow(((abs(b1 - b2) + abs(g1 - g2) + abs(r1 - r2)) ), 2);
        }
    }
    return sum / (width * height)/3;
}

double PSNR::calculate(int depth, double MSE)
{
    double MAX = getBitDepth(depth);
    double result = 20 * log10(MAX / MSE);
    return result;
}



