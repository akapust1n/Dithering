#ifndef DATAREAD_H
#define DATAREAD_H
#include <DitherManager.h>
#include <Magick++.h>
#include <QImage>
#include <QPixmap>
#include <QString>
using namespace std;

class DataManager {
public:
    enum kind {
        IMAGE_FOR_DITH,
        IMAGE_SAMPLE,
        IMAGE_DITHERED,
        IMAGE_BEFORE
    };

    ~DataManager();
    void convertTo4Bit(QImage*& image);
    void loadImage(QString filename, kind kindImage);
    QImage** getImage(kind kindImage);
    static QString getImageName(dither_kind kind = OTHER);

private:
    QImage* imageForDith = nullptr;
    QImage* imageSample = nullptr;
    QImage* imageDithered = nullptr;
    QImage* imageBefore = nullptr;
    QImage* openImage(QString filename);
};

#endif // DATAREAD_H
