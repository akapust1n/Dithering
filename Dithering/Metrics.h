#ifndef METRICS_H
#define METRICS_H
#include <QColor>
#include <memory>
#include <QImage>
class Metrics{
public:
    virtual double getValue(std::shared_ptr<QImage> &image1, std::shared_ptr<QImage> &image2)=0;
protected:
    double getBitDepth(int depth);
};
class PSNR:public Metrics{
public:
     virtual double getValue(std::shared_ptr<QImage>& image1, std::shared_ptr<QImage>& image2);
private:
    double getMSE(std::shared_ptr<QImage> image1, std::shared_ptr<QImage> image2);
    double calculate(int depth, double MSE);

};

class SSIM:public Metrics{
public:
     virtual double getValue(std::shared_ptr<QImage> & _image1, std::shared_ptr<QImage>& _image2);

private:
    double avg(std::shared_ptr<QImage> & img);
    double var(std::shared_ptr<QImage> & img, double mu);
    double cov(std::shared_ptr<QImage> & img1, std::shared_ptr<QImage> & img2, double mu1, double mu2);
    double calculate();
    double ux; //среднее х
    double uy;
    double ox;
    double oy;
    double oxy;
    double getC1(int depth);
    double getC2(int depth);
};

#endif // METRICS_H