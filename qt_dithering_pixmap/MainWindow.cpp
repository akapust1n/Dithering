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
    ui->progressBar->setValue(5);
    mainmanager.loadFile(sourceName, DataManager::IMAGE_FOR_DITH);
    mainmanager.changeDepth(4, DataManager::IMAGE_FOR_DITH);
    ui->progressBar->setValue(10);
    mainmanager.init(DataManager::IMAGE_FOR_DITH);
    mainmanager.dither(WHITE_DITH);
    ui->progressBar->setValue(20);
    mainmanager.dither(VIOLET_DITH);
    ui->progressBar->setValue(45);
    mainmanager.dither(BROWN_DITH);
    ui->progressBar->setValue(60);
    mainmanager.dither(PINK_DITH);
    ui->progressBar->setValue(75);
    mainmanager.dither(BLUE_DITH);
    ui->progressBar->setValue(100);
}

void MainWindow::on_pushButton_3_clicked()
{
    QString sourceName = QFileDialog::getOpenFileName(this, QString::fromUtf8("Открыть файл"),
        QDir::currentPath(), "images (*.*)");
    mainmanager.loadFile(sourceName, DataManager::IMAGE_SAMPLE);
    mainmanager.initSampleImage();

}

void MainWindow::on_pushButton_2_clicked()
{
    QString sourceName = QFileDialog::getOpenFileName(this, QString::fromUtf8("Открыть файл"),
        QDir::currentPath(), "images (*.*)");
    mainmanager.loadFile(sourceName, DataManager::IMAGE_DITHERED);
    mainmanager.initDitheredImage();
   double ssim = mainmanager.getSSIM();
   ui->Results->append("SSIM: ");
   ui->Results->append(QString::number(ssim));
}
