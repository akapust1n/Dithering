#ifndef SSIM_H
#define SSIM_H
#include "Method.h"

class SSIM : public Method {
public:
    virtual double getResult(QImage* _image1, QImage* _image2);

private:
    double avg(QImage* img);
    double var(QImage* img, double mu);
    double cov(QImage* img1, QImage* img2, double mu1, double mu2);
    double calculate(int64_t depth);
    double ux; //среднее х
    double uy;
    double ox;
    double oy;
    double oxy;
    double getC1(int64_t depth);
    double getC2(int64_t depth);
};

#endif // SSIM_H
