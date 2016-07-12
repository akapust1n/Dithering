#include <Dithering.h>
#include <cstdlib>
//----------------------------------белый шум-------------------------------------
void WhiteNoiseDithering::Dither(QImage& image1, QImage& image2)
{
    image2 = image1;
    int width = image2.width();
    int height = image2.height();
    int number = 0;
    QRgb value;
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++) {
            number = rand() % 256;

           // image2.setPixelColor(i, j, NewCOLOR(image1.pixelColor(i, j), number));
           // image2.setPixel(i,j,NewCOLOR(image1.pixelColor(i, j), number));
          //  image2.setColor(i*j+j,NewCOLOR(image1.pixelColor(i, j),number));
           //image2.setPixel(i,j,i*j+j);
            //image2.setPixel(i, j,temp_rgb.qBlue() )
        }
    image2.save("WHITE_noise.bmp", "bmp");
}
QRgb Dithering::NewCOLOR(QColor pixel, int number)
{
   int red, blue,green;


    if (pixel.blue() > number)
        blue = 255;
    else
        blue = 0;
    if (pixel.red() > number)
        red = 255;
    else
        red = 0;
    if (pixel.green() > number)
        green = 255;
    else
        green = 0;
    QRgb value;
    value= qRgb(red,green,blue);

    return value;
}
//---------------------------------коричневый шум--------------
/*
void BrownNoiseDithering::Dither(QImage& image1, QImage& image2)

{
    image2 = image1;
    int width = image2.width();
    int height = image2.height();
    int number[3];
    number[0] = rand() % 256;
    number[1] = rand() % 256;
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++) {

            number[2] = 0.5 * (number[0] + number[1]);
            if (number[2] > 255)
                number[2] = 255;
            image2.setPixelColor(i, j, NewCOLOR(image1.pixelColor(i, j), number[2]));
            number[1] = number[0];
            number[0] = rand()%256;
        }
    image2.save("BROWN_noise.bmp", "bmp");
}
*/
