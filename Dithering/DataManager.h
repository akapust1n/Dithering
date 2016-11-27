#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include <DataManager.h>
#include <QImage>
#include <QString>
#include <memory>
class DataManager {
public:
    enum kind {
        start_image,
        converted_image,
        dithered_image
    };
    void loadImage(QString filename, kind kindImage);
    void loadImage(std::shared_ptr<QImage>& image);
    std::shared_ptr<QImage> &getImage(kind kindImage);
    static QString getImageName(kind kindImage);

private:
    std::shared_ptr<QImage> start_image1;
    std::shared_ptr<QImage> converted_image1;
    std::shared_ptr<QImage> dithered_image1;
};

#endif // DATAMANAGER_H
