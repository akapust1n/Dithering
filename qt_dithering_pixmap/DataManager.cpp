#include <DataManager.h>
#include <iostream>
//открываем изображение и приводим его к 8ми-битному
//не очень хорошая логика, но пойдет
QImage* DataManager::openImage(QString filename)
{

    QImage *image1 = new QImage(filename);
    cout<<image1->depth();

     //cout<<image1->depth();
     //convertTo4Bit(image1);

    return image1;
}

void DataManager::convertTo4Bit(QImage *&image)
{
    *image= image->convertToFormat(QImage::Format_Indexed8,Qt::AvoidDither);
    image->save("4bit.bmp","bmp");

}
