#ifndef YLIOUMADITH_H
#define YLIOUMADITH_H
#include "Dithering.h"
class Yliluoma1 : public Dithering {
private:
    struct MixingPlan
    {
        unsigned colors[4];
        double ratio;
        /* 0 = always index1, 1 = always index2, 0.5 = 50% of both */
        /* 4 = special three or four-color dither */
    };
public:
    Yliluoma1();
    virtual int Dither(std::shared_ptr<QImage>& image1, std::shared_ptr<QImage>& image2);
    virtual int Dither(std::shared_ptr<QImage>& image1);



private:
#define d(x) x / 64.0
    constexpr static const double map1[8 * 8] = {
        d(0), d(48), d(12), d(60), d(3), d(51), d(15), d(63),
        d(32), d(16), d(44), d(28), d(35), d(19), d(47), d(31),
        d(8), d(56), d(4), d(52), d(11), d(59), d(7), d(55),
        d(40), d(24), d(36), d(20), d(43), d(27), d(39), d(23),
        d(2), d(50), d(14), d(62), d(1), d(49), d(13), d(61),
        d(34), d(18), d(46), d(30), d(33), d(17), d(45), d(29),
        d(10), d(58), d(6), d(54), d(9), d(57), d(5), d(53),
        d(42), d(26), d(38), d(22), d(41), d(25), d(37), d(21)
    };
#undef d
    unsigned pal[216];
//   constexpr static const unsigned pal[16] =
//    {0x080000,0x201A0B,0x432817,0x492910,
//     0x234309,0x5D4F1E,0x9C6B20,0xA9220F,
//     0x2B347C,0x2B7409,0xD0CA40,0xE8A077,
//     0x6A94AB,0xD5C4B3,0xFCE76E,0xFCFAE2 };
    double ColorCompare(int r1, int g1, int b1, int r2, int g2, int b2);
    double EvaluateMixingError(int r,int g,int b,
                               int r0,int g0,int b0,
                               int r1,int g1,int b1,
                               int r2,int g2,int b2,
                               double ratio);
    MixingPlan DeviseBestMixingPlan(unsigned color);
    QColor rgbToQColor(unsigned rgb);
    unsigned qColorToint(QColor &color);
};



#endif // YLIOUMADITH_H
