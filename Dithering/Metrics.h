#ifndef METRICS_H
#define METRICS_H
#include <QColor>
#include <memory>
#include <QImage>
class Metrics{
public:
    virtual double getValue(std::shared_ptr<QImage> image1, std::shared_ptr<QImage> image2)=0;
protected:
    double getBitDepth(int depth);
};
class PSNR:public Metrics{
public:
     virtual double getValue(std::shared_ptr<QImage> image1, std::shared_ptr<QImage> image2);
private:
    double getMSE(std::shared_ptr<QImage> image1, std::shared_ptr<QImage> image2);
    double calculate(int depth, double MSE);

};
class SSIM:public Metrics{
public:
     virtual double getValue(std::shared_ptr<QImage> image1, std::shared_ptr<QImage> image2);

};

#endif // METRICS_H
