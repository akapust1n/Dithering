#include "Metrics.h"
#include <iostream>
double Metrics::getSSIM()
{
   std::cout<<"SSIM_____"<<ssim.getResult(image1, image2);
}

void Metrics::initFirstImage(QImage **image)
{
    image1 = *image;
}

void Metrics::initSecondImage(QImage **image)
{
    image2 = *image;
}
