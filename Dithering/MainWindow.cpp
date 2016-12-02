#include "MainWindow.h"
#include "Magick++.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QPixmap>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(this, SIGNAL(convert_end()), this, SLOT(on_convert_end()));
    for (int i = 0; i < 3; i++)
        scaleFactors[i] = 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    QString sourceName = QFileDialog::getOpenFileName(this, QString::fromUtf8("Открыть файл"),
        QDir::currentPath(), "images (*.*)");
    if (!sourceName.isEmpty()) {
        mainManager.loadImage(sourceName);
        QPixmap temp(DataManager::getImageName(DataManager::start_image));
        width = temp.width();
        height = temp.height();
        ui->start_image->setPixmap(temp);
        ui->start_image->resize(temp.size());
        //ui->originalArea->widget()->releaseShortcut()
        std::thread thr(&MainWindow::convert, this);
        thr.detach();
    }
}

void MainWindow::on_pushButton_clicked()
{
    /* enum kind_dither {
        white_noise,
        blue_noise,
        brown_noise,
        red_noise,
        violet_noise
        floyd_sd,
        false_floyd_sd,
        jjn
    };*/
    int index = ui->comboBox->currentIndex();
    DitherManager::kind_dither kindDither;
    switch (index) {
    case 0: {
        kindDither = DitherManager::white_noise;
        break;
    }
    case 1: {
        kindDither = DitherManager::blue_noise;
        break;
    }
    case 2: {
        kindDither = DitherManager::brown_noise;
        break;
    }
    case 3: {
        kindDither = DitherManager::violet_noise;
        break;
    }
    case 4: {
        kindDither = DitherManager::pink_noise;
        break;
    }
    case 5: {
        kindDither = DitherManager::floyd_sd;
        break;
    }
    case 6: {
        kindDither = DitherManager::false_floyd_sd;
        break;
    }
    case 7: {
        kindDither = DitherManager::jjn;
        break;
    }
    default:
        kindDither = DitherManager::white_noise;
    }

    int _time = mainManager.dither(kindDither);

    QPixmap temp(DataManager::getImageName(DataManager::dithered_image));
    ui->w_dith->setPixmap(temp);
    ui->w_dith->resize(temp.size());

    QString psnr;
    psnr = psnr.number(mainManager.getMetrics(MetricsManager::psnr, DataManager::dithered_image));
    ui->textEdit->append(ui->comboBox->currentText());
    ui->textEdit->append("PSNR: " + psnr);
    QString ssim;
    ssim = ssim.number(mainManager.getMetrics(MetricsManager::ssim, DataManager::dithered_image));
    ui->textEdit->append("SSIM: " + ssim);
    QString time;
    time = time.number(_time);
    ui->textEdit->append("Time, ms: " + time);
}

void MainWindow::on_convert_end()
{
    QPixmap temp2(DataManager::getImageName(DataManager::converted_image));
    ui->bad_image->setPixmap(temp2);
    ui->bad_image->resize(temp2.size());

    QString psnr;
    psnr = psnr.number(mainManager.getMetrics(MetricsManager::psnr, DataManager::converted_image));
    ui->textEdit->append("PSNR web-safe image: " + psnr);

    QString ssim;
    ssim = ssim.number(mainManager.getMetrics(MetricsManager::ssim, DataManager::converted_image));
    ui->textEdit->append("SSIM web-safe image: " + ssim);
}

void MainWindow::convert()
{
    std::lock_guard<std::mutex> guard(_mutex);
    mainManager.convert();
    emit convert_end();
}

void MainWindow::on_plus_clicked()
{
    double scale = 1.2;

    int tab = ui->tabWidget->currentIndex();
    switch (tab) {
    case (0): {
        auto temp = ui->start_image->pixmap();
        scaleFactors[0] *= scale;
        if (scaleFactors[0] > 4)
            scaleFactors[0] = 4;
        ui->start_image->setPixmap(temp->scaled(width * scaleFactors[0], height * scaleFactors[0], Qt::KeepAspectRatio, Qt::SmoothTransformation));
        break;
    }
    case (1): {
        auto temp = ui->w_dith->pixmap();
        scaleFactors[1] *= scale;
        if (scaleFactors[1] > 4)
            scaleFactors[1] = 4;

        ui->w_dith->setPixmap(temp->scaled(width * scaleFactors[1], height * scaleFactors[1], Qt::KeepAspectRatio, Qt::SmoothTransformation));
        break;
    }
    case (2): {
        auto temp = ui->bad_image->pixmap();
        scaleFactors[2] *= scale;
        if (scaleFactors[2] > 4)
            scaleFactors[2] = 4;

        ui->bad_image->setPixmap(temp->scaled(width * scaleFactors[2], height * scaleFactors[2], Qt::KeepAspectRatio, Qt::SmoothTransformation));
        break;
    }
    }
}
#include <iostream>
void MainWindow::on_minus_clicked()
{
    double scale = 0.8;

    int tab = ui->tabWidget->currentIndex();
    switch (tab) {
    case (0): {
        auto temp = ui->start_image->pixmap();
        scaleFactors[0] *= scale;
        if (scaleFactors[0] < 0.4)
            scaleFactors[0] = 0.4;

        ui->start_image->setPixmap(temp->scaled(width * scaleFactors[0], height * scaleFactors[0], Qt::KeepAspectRatio, Qt::SmoothTransformation));
        break;
    }
    case (1): {
        auto temp = ui->w_dith->pixmap();
        scaleFactors[1] *= scale;
        if (scaleFactors[1] < 0.4)
            scaleFactors[1] = 0.4;

        ui->w_dith->setPixmap(temp->scaled(width * scaleFactors[1], height * scaleFactors[1], Qt::KeepAspectRatio, Qt::SmoothTransformation));
        break;
    }
    case (2): {
        auto temp = ui->bad_image->pixmap();
        scaleFactors[2] *= scale;
        if (scaleFactors[2] < 0.4)
            scaleFactors[2] = 0.4;

        ui->bad_image->setPixmap(temp->scaled(width * scaleFactors[2], height * scaleFactors[2], Qt::KeepAspectRatio, Qt::SmoothTransformation));
        break;
    }
    }
}
