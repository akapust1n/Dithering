#ifndef MAINMANAGER_H
#define MAINMANAGER_H
#include <QString>
#include <DataManager.h>
#include "Metrics.h"
#include <DataManager.h>
#include <DitherManager.h>

class MainManager
{
public:

   void dither(dither_kind kind);
   void init(DataManager::kind kindImage);
   void loadFile(QString &fname, DataManager::kind kindImage);
   void changeDepth(int depthk, DataManager::kind kindImage);
   void initSampleImage();
   void initDitheredImage();
   double getSSIM();
private:
   DitherManager ditherManager;
   QString filename;
   DataManager dataManager;
   Metrics metrics;


};

#endif // MAINMANAGER_H
