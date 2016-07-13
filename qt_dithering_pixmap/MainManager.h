#ifndef MAINMANAGER_H
#define MAINMANAGER_H
#include <QString>
#include <DataRead.h>
#include <QImage>
#include <Dithering.h>
enum dither_kind {
    WHITE_DITH, BROWN_DITH,PINK_DITH
};
class MainManager
{
public:
   void loadFile(QString &fname);
   void dither(dither_kind kind);
private:
   QString filename;
   DataRead dataread;
   QImage image1;
   QImage image2;
   QImage image_temp;
   WhiteNoiseDithering wndithering;
   BrownNoiseDithering bndithering;
   PinkNoiseDithering pndithering;
};

#endif // MAINMANAGER_H
