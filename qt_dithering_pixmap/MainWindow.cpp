#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <memory>
MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->progressBar->setValue(0);
    QString sourceName = QFileDialog::getOpenFileName(this, QString::fromUtf8("Открыть файл"),
        QDir::currentPath(), "images (*.*)");
    ui->progressBar->setValue(5);
    mainmanager.loadFile(sourceName, DataManager::IMAGE_FOR_DITH);
    mainmanager.saveAsFile(4, DataManager::IMAGE_FOR_DITH);
    mainmanager.init(DataManager::IMAGE_FOR_DITH);\

    QPixmap image1("/home/alexey/15/cg_cursach/build/4bit.bmp");
    ui->img1->setPixmap(image1);
    QPixmap image2("/home/alexey/15/cg_cursach/build/0_PINK_noise.bmp");
    ui->img2->setPixmap(image2);

    mainmanager.loadFile(DataManager::getImageName(NO_DITH), DataManager::IMAGE_DITHERED);
    mainmanager.init(DataManager::IMAGE_DITHERED);\
    mainmanager.loadFile(DataManager::getImageName(), DataManager::IMAGE_SAMPLE);
    mainmanager.init(DataManager::IMAGE_SAMPLE);
    double ssim = mainmanager.getSSIM();
    ui->Results->append("Starter DSSIM: ");
    ui->Results->append(QString::number(ssim));

    double psnr = mainmanager.getPSNR();
    ui->Results->append("Starter PSNR: ");
    ui->Results->append(QString::number(psnr));
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
     */
    int _index = ui->comboBox->currentIndex();
    switch (_index) {
    case 0: {
        mainmanager.dither(WHITE_DITH);
        break;
    }
    case 1: {
        mainmanager.dither(BLUE_DITH);
        break;
    }
    case 2: {
        mainmanager.dither(BROWN_DITH);
        break;
    }
    case 3: {
        mainmanager.dither(VIOLET_DITH);
        break;
    }
    case 4: {
        mainmanager.dither(PINK_DITH);
        break;
    }
    };

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
