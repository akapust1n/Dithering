#ifndef MAINMANAGER_H
#define MAINMANAGER_H
#include <QString>
#include <DataManager.h>

#include <DataManager.h>
#include <DitherManager.h>

class MainManager
{
public:

   void loadFile(QString &fname, QImage *&image1);
   void dither(dither_kind kind);
   void init(QImage *image);   
   void changeDepth(int depth, QImage *image);
private:
   DitherManager ditherManager;
   QString filename;
   DataManager dataManager;


};

#endif // MAINMANAGER_H
