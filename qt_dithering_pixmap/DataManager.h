#ifndef DATAREAD_H
#define DATAREAD_H
#include <QPixmap>
#include <QString>
#include <QImage>
using namespace std;

class DataManager {
public:
    QImage* openImage(QString filename);
    void convertTo4Bit(QImage *&image);

};

#endif // DATAREAD_H
