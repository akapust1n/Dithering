#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <memory>
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString sourceName = QFileDialog::getOpenFileName(this, QString::fromUtf8("Открыть файл"),
        QDir::currentPath(), "images (*.*)");
    if(!sourceName.isEmpty()) {
    mainmanager.loadFile(sourceName, DataManager::IMAGE_FOR_DITH);
    mainmanager.saveAsFiles(4, DataManager::IMAGE_FOR_DITH);
    mainmanager.init(DataManager::IMAGE_FOR_DITH);
    QPixmap temp(DataManager::getImageName(NO_DITH));
    ui->img1->setPixmap(temp);


    mainmanager.loadFile(DataManager::getImageName(NO_DITH), DataManager::IMAGE_DITHERED);
    mainmanager.init(DataManager::IMAGE_DITHERED);
    mainmanager.loadFile(DataManager::getImageName(), DataManager::IMAGE_SAMPLE);
    mainmanager.init(DataManager::IMAGE_SAMPLE);
    double ssim = mainmanager.getSSIM();
    ui->Results->append("Starter DSSIM: ");
    ui->Results->append(QString::number(ssim));

    double psnr = mainmanager.getPSNR();
    ui->Results->append("Starter PSNR: ");
    ui->Results->append(QString::number(psnr));
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    //    QString sourceName = QFileDialog::getOpenFileName(this, QString::fromUtf8("Открыть файл"),
    //        QDir::currentPath(), "images (*.*)");
    //    mainmanager.loadFile(sourceName, DataManager::IMAGE_SAMPLE);
    //    mainmanager.initSampleImage();
}

void MainWindow::on_pushButton_2_clicked()
{
    /*
     * 0) White Noise
     * 1)Blue noise
     * 2)Brown noise
     * 3)Violet noise
     * 4)Pink noise
     * 5)Floyd-Steindberg
     */
    int _index = ui->comboBox->currentIndex();
    switch (_index) {
    case 0: {
        mainmanager.dither(WHITE_DITH);
        mainmanager.loadFile(DataManager::getImageName(WHITE_DITH), DataManager::IMAGE_DITHERED);
        QPixmap temp(DataManager::getImageName(WHITE_DITH));
        ui->img2->setPixmap(temp);

        break;
    }
    case 1: {
        mainmanager.dither(BLUE_DITH);
        mainmanager.loadFile(DataManager::getImageName(BLUE_DITH), DataManager::IMAGE_DITHERED);
        QPixmap temp(DataManager::getImageName(BLUE_DITH));
        ui->img2->setPixmap(temp);
        break;
    }
    case 2: {
        mainmanager.dither(BROWN_DITH);
        mainmanager.loadFile(DataManager::getImageName(BROWN_DITH), DataManager::IMAGE_DITHERED);
        QPixmap temp(DataManager::getImageName(BROWN_DITH));
        ui->img2->setPixmap(temp);
        break;
    }
    case 3: {
        mainmanager.dither(VIOLET_DITH);
        mainmanager.loadFile(DataManager::getImageName(VIOLET_DITH), DataManager::IMAGE_DITHERED);
        QPixmap temp(DataManager::getImageName(VIOLET_DITH));
        ui->img2->setPixmap(temp);
        break;
    }
    case 4: {
        mainmanager.dither(PINK_DITH);
        mainmanager.loadFile(DataManager::getImageName(PINK_DITH), DataManager::IMAGE_DITHERED);
        QPixmap temp(DataManager::getImageName(PINK_DITH));
        ui->img2->setPixmap(temp);
        break;
    }
    case 5: {
        mainmanager.dither(FLOYDSD_DITH);
        mainmanager.loadFile(DataManager::getImageName(FLOYDSD_DITH), DataManager::IMAGE_DITHERED);
        QPixmap temp(DataManager::getImageName(FLOYDSD_DITH));
        ui->img2->setPixmap(temp);
        break;
    }
    };

    mainmanager.init(DataManager::IMAGE_DITHERED);

    ui->Results->append(ui->comboBox->currentText());
    double ssim = mainmanager.getSSIM();
    ui->Results->append("SSIM: ");
    ui->Results->append(QString::number(ssim));

    double psnr = mainmanager.getPSNR();
    ui->Results->append("PSNR: ");
    ui->Results->append(QString::number(psnr));

    //    QString sourceName = QFileDialog::getOpenFileName(this, QString::fromUtf8("Открыть файл"),
    //        QDir::currentPath(), "images (*.*)");
    //    mainmanager.loadFile(sourceName, DataManager::IMAGE_DITHERED);
    //    mainmanager.initDitheredImage();
    //   double ssim = mainmanager.getSSIM();
    //   ui->Results->append("SSIM: ");
    //   ui->Results->append(QString::number(ssim));

    //   double psnr = mainmanager.getPSNR();
    //   ui->Results->append("PSNR: ");
    //   ui->Results->append(QString::number(psnr));
}
