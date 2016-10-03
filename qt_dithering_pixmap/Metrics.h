#ifndef METRICS_H
#define METRICS_H
#include <QImage>
#include <PSNR.h>
#include <SSIM.h>


class Metrics
{
public:
    double getSSIM();
    double getPSNR();
    void initFirstImage(QImage **image);
    void initSecondImage(QImage **image);

private:
    SSIM ssim;
    PSNR psnr;
    QImage *image1;
    QImage *image2;
};

#endif // METRICS_H
