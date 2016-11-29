#include "Metrics.h"
#include <cmath>
#include <cmath>
#include <iomanip>
#include <iostream>

double Metrics::getBitDepth(int depth)
{
    return (pow(2, depth) - 1);
}

double PSNR::getValue(std::shared_ptr<QImage>& image1, std::shared_ptr<QImage>& image2)
{
    double result = calculate(8, sqrt(getMSE(image1, image2)));
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
            sum += pow(((abs(b1 - b2) + abs(g1 - g2) + abs(r1 - r2))), 2);
        }
    }
    return sum / (width * height) / 3;
}

double PSNR::calculate(int depth, double MSE)
{
    double MAX = getBitDepth(depth);
    double result = 20 * log10(MAX / MSE);
    return result;
}

double SSIM::getValue(std::shared_ptr<QImage>& _image1, std::shared_ptr<QImage>& _image2)
{
    ux = avg(_image1);
    uy = avg(_image2);

    ox = var(_image1, ux);
    oy = var(_image2, uy);
    //std::cout << "SR___________" << avg1 << std::endl;
    // auto var1= var(_image1, avg1);
    // std::cout << "VR___________" << var1 << std::endl;
    //   std::cout << "there";
    oxy = cov(_image1, _image2, ux, uy);
    std::cout << std::endl
              << "Comparsion " << ox << " vs " << oxy << std::endl;
    double temp = calculate();
    std::cout << _image1->depth() << "DEPTH" << std::endl;
    std::cout << std::setprecision(15) << std::fixed << "Result " << temp << std::endl;
    return temp;
}

double SSIM::avg(std::shared_ptr<QImage>& img)
{
    int width = img->width() ;
    int height = img->height() ;
    int x, y, b = 0, g = 0, r = 0;
    double col = 0;

    for (x = 0; x < width; x++) {
        for (y = 0; y < height; y++) {
            QColor pixel = img->pixel(x, y);

            b = pixel.blue();
            g = pixel.green(); // вот так мы как раз обращаемся к различным компонентам цветов
            r = pixel.red(); // b - blue, r - red, g - green
            col +=( b + g + r);
        }
    }
    return col / (width * height) / 3.0;
}

double SSIM::var(std::shared_ptr<QImage>& img, double mu)
{ //variance

    int width = img->width() ;
    int height = img->height();
    int x, y, b = 0, g = 0, r = 0;

    double col = 0;

    for (x = 0; x <width; x++) {
        for (y = 0; y < height; y++) {

            QColor pixel = img->pixel(x, y);
            b = pixel.blue();
            col += (1.0 * b - mu) * (1.0 * b - mu);
            g = pixel.green();
            col += (1.0 * g - mu)* (1.0 * g - mu);
            r = pixel.red();
            col += (1.0 * r - mu) * (1.0 * r - mu);
        }
    }
    return col / (width * height) / 3;
}

double SSIM::cov(std::shared_ptr<QImage>& img1, std::shared_ptr<QImage>& img2, double mu1, double mu2)
{ //covariance

    int x, y;
    double b1 = 0, g1 = 0, b2 = 0, g2 = 0, r1 = 0, r2 = 0;
    double col = 0;
    int width = img1->width() ;
    int height = img1->height() ;

    for (x = 0; x < width; x++) {
        for (y = 0; y < height; y++) {
            QColor pixel1 = img1->pixel(x, y);
            QColor pixel2 = img2->pixel(x, y);

            b1 = pixel1.blue();
            g1 = pixel1.green();
            r1 = pixel1.red();

            b2 = pixel2.blue();
            g2 = pixel2.green();
            r2 = pixel2.red();
            // col += abs((r1 * 1.0 - mu1) * (r2 *1.0 - mu2));
            // col+= (((b1-mu1)+(g1-mu1)+(r1-mu1))/3)*(((b2-mu2)+(g2-mu2)+(r2-mu2))/3);
            //модули поставлены ПОТОМУ ЧТО так точнее (не знаю почему)
            //col += std::abs((b1 - mu1) * (b2 - mu2)) + std::abs((g1 - mu1) * (g2 - mu2)) + std::abs((r1 - mu2) * (r2 - mu2));
            col += (((b1 - mu1) * (b2 - mu2)) + ((g1 - mu1) * (g2 - mu2)) + ((r1 - mu1) * (r2 - mu2)));
        }
    }
    std::cout << "Comparsion mu " << mu1 << " " << mu2 << std::endl;
    return col / (width * height) / 3.0;
}

double SSIM::calculate()
{
    double temp1 = 2.0 * oxy;
    double temp2 = ox + oy;
    double temp3 = temp1 * temp2;
    std::cout << "temp1 " << temp1 << std::endl;
    std::cout << "temp2 " << temp2 << std::endl;

    //    double result_part1 = (2.0 * ux * uy + 1.0*getC1(depth)) * (2.0 * oxy + 1.0*getC2(depth));
    //    double result_part2 = (ux * ux + uy * uy +1.0 *getC1(depth)) * (ox + oy + 1.0*getC2(depth));
//        double result_part1 = (2.0 * ux * uy +6.5025) * (2.0 * oxy +58.5225);
//        double result_part2 = (ux * ux + uy * uy +6.5025) * (ox + oy +58.5225);
    //заранее посчитал c1 и с2 для сравнения 8 бит на канал и 8 бит всего.
    double result_part1 = (2.0 * ux * uy + 6.5025) * (2.0 * oxy + 0.0324);
    double result_part2 = (ux * ux + uy * uy + 6.5025) * (ox + oy + 0.0324);

    std::cout << "result_part1 " << result_part1 << std::endl;
    std::cout << "result_part2 " << result_part2 << std::endl;
    return result_part1 / result_part2;
}

double SSIM::getC1(int depth)
{
    double bitnost = getBitDepth(depth);
    return (0.01 * bitnost) * (0.01 * bitnost);
}

double SSIM::getC2(int depth)
{
    double bitnost = getBitDepth(depth);
    return (0.03 * bitnost) * (0.03 * bitnost);
}
