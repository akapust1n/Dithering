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
   void loadFile(QString fname, DataManager::kind kindImage);
   void saveAsFile(int depthk, DataManager::kind kindImage);
   void saveOriginalImage();
   double getSSIM();
   double getPSNR();
private:
   DitherManager ditherManager;
   QString filename;
   DataManager dataManager;
   Metrics metrics;


};

#endif // MAINMANAGER_H
