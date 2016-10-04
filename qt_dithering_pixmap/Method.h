#ifndef METHOD_H
#define METHOD_H
#include <QImage>
class Method{
public:
    virtual double getResult(QImage *image1, QImage *image2)=0;
    double getBitDepth(int depth);
};

#endif // METHOD_H
