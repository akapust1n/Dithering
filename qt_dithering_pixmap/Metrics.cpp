#include "Metrics.h"
#include <iostream>
double Metrics::getSSIM()
{
    return ssim.getResult(image1, image2);
}

double Metrics::getPSNR()
{
    return  psnr.getResult(image1,image2);
}

void Metrics::initFirstImage(QImage **image)
{
    image1 = *image;
}

void Metrics::initSecondImage(QImage **image)
{
    image2 = *image;
}
