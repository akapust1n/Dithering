#ifndef PSNR_H
#define PSNR_H
#include "Method.h"

class PSNR: public Method{
   virtual double getResult(QImage *image1, QImage *image2);
};

#endif // PSNR_H
