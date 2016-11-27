#ifndef MAINMANAGER_H
#define MAINMANAGER_H
#include <QImage>
#include "DataManager.h"
#include <QString>
#include <DitherManager.h>
#include "MetricsManager.h"
class MainManager
{
public:
    void loadImage(QString filename);
    void dither(DitherManager::kind_dither kindDither);
    double getMetrics(MetricsManager::kind_metrics kindMetrics);
private:
    DataManager dataManager;
    DitherManager ditherManager;
    MetricsManager metricsManager;
};

#endif // MAINMANAGER_H
