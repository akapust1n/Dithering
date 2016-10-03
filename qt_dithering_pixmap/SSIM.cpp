#include "math.h"
#include <SSIM.h>
#include <cmath>
#include <iostream>

double SSIM::getResult(QImage* _image1, QImage* _image2)
{
    ux = avg(_image1);
    uy = avg(_image2);

    ox = var(_image1, ux);
    oy = var(_image2, uy);
    //std::cout << "SR___________" << avg1 << std::endl;
    // auto var1= var(_image1, avg1);
    // std::cout << "VR___________" << var1 << std::endl;
    std::cout << "there";
    oxy = cov(_image1, _image2, ux, uy);
    std::cout << std::endl
              << "Comparsion " << ox << " vs " << oxy << std::endl;

    return calculate(_image1->depth());
}

double SSIM::avg(QImage* img)
{
    int width = img->width() - 1;
    int height = img->height() - 1;
    int x, y, b = 0, g = 0, r = 0;
    double col = 0;
    ;

    for (x = 0; x <= width; x++) {
        for (y = 0; y <= height; y++) {
            QColor pixel = img->pixel(x, y);

            //   b = pixel.blue();
            // g = pixel.green(); // вот так мы как раз обращаемся к различным компонентам цветов
            r = pixel.red(); // b - blue, r - red, g - green
            // col += b + g + r;
            col += r;
        }
    }
    return col / (width * height);
}

double SSIM::var(QImage* img, double mu)
{ //variance

    int width = img->width() - 1;
    int height = img->height() - 1;
    int x, y, b = 0, g = 0;
    double r = 0;
    double col = 0;

    for (x = 0; x <= width; x++) {
        for (y = 0; y <= height; y++) {

            QColor pixel = img->pixel(x, y);
            // b = pixel.blue();
            //  col += (abs(1.0 * b - mu)) * (abs(1.0 * b - mu));
            // g = pixel.green();
            //  col += (abs(1.0 * g - mu)) * (abs(1.0 * g - mu));
            r = pixel.red() * 1.0;
            col += abs(((r - mu)) * ((r - mu)));
        }
    }
    return col / (width * height);
}

double SSIM::cov(QImage* img1, QImage* img2, double mu1, double mu2)
{ //covariance

    int x, y, b1 = 0, g1 = 0, b2 = 0, g2 = 0, r1 = 0, r2 = 0;
    double col = 0;
    int width = img1->width() - 1;
    int height = img1->height() - 1;

    for (x = 0; x <= width; x++) {
        for (y = 0; y <= height; y++) {
            QColor pixel1 = img1->pixel(x, y);
            QColor pixel2 = img2->pixel(x, y);

            // b1 = pixel1.blue();
            // g1 = pixel1.green();
            r1 = pixel1.red();

            // b2 = pixel2.blue();
            // g2 = pixel2.green();
            r2 = pixel2.red();
            col += abs((r1 * 1.0 - mu1) * (r2 *1.0 - mu2));
            // col+= (((b1-mu1)+(g1-mu1)+(r1-mu1))/3)*(((b2-mu2)+(g2-mu2)+(r2-mu2))/3);
            //col += (b1 - mu1) * (b2 - mu2) + (g1 - mu1) * (g2 - mu2) + (r1 - mu2) * (r2 - mu2);
        }
    }

    return col / (width * height);
}

double SSIM::calculate(int64_t depth)
{
    double result_part1 = (2 * ux * uy + getC1(depth)) * (2 * oxy + getC2(depth));
    double result_part2 = (ux * ux + uy * uy + getC1(depth)) * (ox + oy + getC2(depth));
    return result_part1 / result_part2;
}

double SSIM::getC1(int64_t depth)
{
    double bitnost = pow(2, depth) - 1;
    return (0.01 * bitnost) * (0.01 * bitnost);
}

double SSIM::getC2(int64_t depth)
{
    double bitnost = pow(2, depth) - 1;
    return (0.03 * bitnost) * (0.03 * bitnost);
}
