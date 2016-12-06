#include <Magick++.h>
#include <MainManager.h>
#include <iostream>
#include <thread>
#include <QFileInfo>

void MainManager::loadImage(QString filename)
{
    dataManager.loadImage(filename, DataManager::start_image);
    // dataManager.loadImage("empt", DataManager::dithered_image);
    ditherManager.initImages(dataManager.getImage(DataManager::start_image), dataManager.getImage(DataManager::dithered_image));
}

info MainManager::dither(DitherManager::kind_dither kindDither)
{
    //пока не знаю как распараллелить
    //    auto dither = [this](DitherManager::kind_dither kindDither)->int{

    //        int time = ditherManager.Dither(kindDither);
    //        convert(kindDither);
    //    };
    //    std::thread newDither(dither);
    info result;
    result.timeDither = ditherManager.Dither(kindDither);
    result.imageSize = convert(kindDither);

    dataManager.loadImage(ditherManager.getImage());
    return result;
}
double MainManager::getMetrics(MetricsManager::kind_metrics kindMetrics, DataManager::kind kindImage)
{
    std::shared_ptr<QImage> image1;
    std::shared_ptr<QImage> image2;
    image1 = dataManager.getImage(DataManager::start_image);
    if (kindImage == DataManager::dithered_image) {
        image2 = dataManager.getImage(DataManager::dithered_image);
    } else {
        image2 = dataManager.getImage(DataManager::converted_image);
    }
    if (!image2.get())
        std::cout << "Empty image2 in MainManager" << std::endl;
    if (!image1.get())
        std::cout << "Empty image1" << std::endl;

    return metricsManager.getMetrics(image1, image2, kindMetrics);
}

//плохо, что две функции, их МОЖНО слить в одну(наверное)
void MainManager::convert()
{
    QString filename = DataManager::getImageName(DataManager::start_image);
    Magick::Image image;
    Magick::Image netscape;
    try {
        netscape.read("netscape.gif");
        std::cout << filename.toStdString() << std::endl;
        const std::string name = filename.toStdString();
        image.read(name.c_str());
        image.map(netscape, false);
        image.write(DataManager::getImageName(DataManager::converted_image).toStdString());

    } catch (Magick::Exception& error_) {
        std::cout << "cant read file";
    }
    dataManager.loadImage(DataManager::getImageName(DataManager::converted_image), DataManager::converted_image);
}

//return new and old file sizes
fileSizes MainManager::convert(DitherManager::kind_dither kind)
{
    QString filename = DitherManager::getImageName(kind);
    Magick::Image image;
    Magick::Image netscape;
    try {
        netscape.read("netscape.gif");
        std::cout << filename.toStdString() << std::endl;
        const std::string name = filename.toStdString();
        image.read(name.c_str());
        image.map(netscape, false);
        image.write(DitherManager::getImageName(kind, true).toStdString());

    } catch (Magick::Exception& error_) {
        std::cout << "cant read file";
    }
    QFileInfo newFile(DitherManager::getImageName(kind,true));
    QFileInfo oldFile(DataManager::getImageName(DataManager::start_image));
    fileSizes result;
    result.newFileSize =static_cast<int>(newFile.size()/1024);
    result.oldFileSize = static_cast<int>(oldFile.size()/1024);
    return  result;
    //dataManager.loadImage(DataManager::getImageName(DataManager::converted_image), DataManager::converted_image);
}
