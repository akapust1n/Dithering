#ifndef PSNR_H
#define PSNR_H
#include "Method.h"

class PSNR : public Method {
public:
    virtual double getResult(QImage* image1, QImage* image2);

private:
    double getMSE(QImage* image1, QImage* image2);
    double calculate(int depth, double MSE);
};

#endif // PSNR_H
