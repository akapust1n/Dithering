#include <Dithering.h>
#include <cstdlib>
void WhiteNoiseDithering::Dither(QImage& image1, QImage& image2)
{
    image2 = image1;
    int width = image2.width();
    int height = image2.height();
    int number = 0;

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++) {
            number = rand() % 256;

           image2.setPixelColor(i,j,Compare(image1.pixelColor(i,j),number));

            //image2.setPixel(i, j,temp_rgb.qBlue() )
        }
    image2.save("dithered.bmp","bmp");
}

QColor WhiteNoiseDithering::Compare(QColor  pixel, int number)
{
     QColor pixel_temp;


     if(pixel.blue()>number)
         pixel_temp.setBlue(255);
     else
         pixel_temp.setBlue(0);
     if(pixel.red()>number)
         pixel_temp.setRed(255);
     else
         pixel_temp.setRed(0);
     if(pixel.green()>number)
         pixel_temp.setGreen(255);
     else
         pixel_temp.setGreen(0);
 return pixel_temp;

 }
