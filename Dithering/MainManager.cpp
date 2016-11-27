#include <Magick++.h>
#include <MainManager.h>
#include <iostream>
void MainManager::loadImage(QString filename)
{
    dataManager.loadImage(filename, DataManager::start_image);
    // dataManager.loadImage("empt", DataManager::dithered_image);
    ditherManager.initImages(dataManager.getImage(DataManager::start_image), dataManager.getImage(DataManager::dithered_image));
}

void MainManager::dither(DitherManager::kind_dither kindDither)
{
    ditherManager.Dither(kindDither);
    dataManager.loadImage(ditherManager.getImage(), DataManager::dithered_image);
}
double MainManager::getMetrics(MetricsManager::kind_metrics kindMetrics)
{
    auto image1 = dataManager.getImage(DataManager::start_image);
    auto image2 = dataManager.getImage(DataManager::dithered_image);
    if (!image2.get())
        std::cout << "Empty image2 in MainManager" << std::endl;
    if (!image1.get())
        std::cout << "Empty image1" << std::endl;

    return metricsManager.getMetrics(image1, image2, kindMetrics);
}

void MainManager::convert()
{
    QString filename = DataManager::getImageName(DataManager::start_image);
    Magick::Image image;
    Magick::Image netscape;
    try {
        netscape.read("netscape.gif");
        std::cout<<filename.toStdString()<<std::endl;
        const std::string name = filename.toStdString();
        image.read(name.c_str());
        image.map(netscape, false);
        image.write(DataManager::getImageName(DataManager::converted_image).toStdString());

    } catch (Magick::Exception& error_) {
        std::cout << "cant read file";
    }
}
