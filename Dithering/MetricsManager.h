#ifndef METRICSMANAGER_H
#define METRICSMANAGER_H
#include <Metrics.h>
class MetricsManager{
public:
    enum kind_metrics{
        psnr,
        dssim
    };
    double getMetrics(std::shared_ptr<QImage> image1, std::shared_ptr<QImage> image2,kind_metrics kindMetrics);
private:
    PSNR _psnr;


};

#endif // METRICSMANAGER_H
