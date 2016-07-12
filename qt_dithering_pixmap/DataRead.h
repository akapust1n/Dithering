#ifndef DATAREAD_H
#define DATAREAD_H
#include <QPixmap>
#include <QString>
#include <QImage>
using namespace std;

class DataRead {
public:
    QImage openImage(QString filename);
};

#endif // DATAREAD_H
