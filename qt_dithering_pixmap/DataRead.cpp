#include <DataRead.h>
#include <iostream>
//открываем изображение и приводим его к 8ми-битному
//не очень хорошая логика, но пойдет
QImage DataRead::openImage(QString filename)
{
    QImage image1(filename);
   cout<<image1.depth();
    image1 = image1.convertToFormat(QImage::Format_RGB444);
    image1.save("4bit.bmp","bmp");

     cout<<image1.depth();
    return image1;
}
