#include <MetricsManager.h>

double MetricsManager::getMetrics(std::shared_ptr<QImage> image1, std::shared_ptr<QImage> image2, MetricsManager::kind_metrics kindMetrics)
{
    switch (kindMetrics) {
    case psnr: {
       return  _psnr.getValue(image1, image2);
    }
    default:
        break;
    }
}
