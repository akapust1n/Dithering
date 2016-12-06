#ifndef MAINMANAGER_H
#define MAINMANAGER_H
#include "DataManager.h"
#include "MetricsManager.h"
#include <DitherManager.h>
#include <QImage>
#include <QString>
struct fileSizes {
    int newFileSize = 0;
    int oldFileSize = 0;
};

struct info {
    fileSizes imageSize;
    int timeDither = 0;
};
//in KBytes

class MainManager {
public:
    void loadImage(QString filename);

    info dither(DitherManager::kind_dither kindDither);
    double getMetrics(MetricsManager::kind_metrics kindMetrics, DataManager::kind kindImage);
    void convert();
    fileSizes convert(DitherManager::kind_dither kind);

private:
    DataManager dataManager;
    DitherManager ditherManager;
    MetricsManager metricsManager;
};

#endif // MAINMANAGER_H
