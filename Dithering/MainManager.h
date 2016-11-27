#ifndef MAINMANAGER_H
#define MAINMANAGER_H
#include <QImage>
#include "DataManager.h"
#include <QString>
#include <DitherManager.h>

class MainManager
{
public:
    void loadImage(QString filename);
    void dither(DitherManager::kind_dither kindDither);
private:
    DataManager dataManager;
    DitherManager ditherManager;
};

#endif // MAINMANAGER_H
