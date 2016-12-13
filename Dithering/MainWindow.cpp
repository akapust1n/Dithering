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
    //connect(this,SIGNAL(process_start()),this,SLOT())
    for (int i = 0; i < 3; i++)
        scaleFactors[i] = 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    sourceName = QFileDialog::getOpenFileName(this, QString::fromUtf8("Открыть файл"),
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

        ui->openGLWidget->setFilename(sourceName);

      //  ui->openGLWidget->
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
        jjn,
        yliouma1,
        shader
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
    case 8: {
        kindDither = DitherManager::yliluoma1;
        break;
    }
    case 9: {
        //ui->openGLWidget->
    }
    default:
        kindDither = DitherManager::white_noise;
    }

    auto _info = mainManager.dither(kindDither);

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
    time = time.number(_info.timeDither);
    ui->textEdit->append("Time, mks: " + time);
    QString oldFileSize;
    oldFileSize = oldFileSize.number(_info.imageSize.oldFileSize);
    ui->textEdit->append("OldFileSize, KB: " + oldFileSize);
    QString newFileSize;
    newFileSize = newFileSize.number(_info.imageSize.newFileSize);
    ui->textEdit->append("NewFileSize, KB: " + newFileSize);
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

DitherManager::kind_dither MainWindow::currentDither()
{
    /* enum kind_dither {
        white_noise,
        blue_noise,
        brown_noise,
        red_noise,
        violet_noise
        floyd_sd,
        false_floyd_sd,
        jjn,
        yliouma1
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
    case 8: {
        kindDither = DitherManager::yliluoma1;
        break;
    }
    default:
        kindDither = DitherManager::white_noise;
    }
}

void MainWindow::on_plus_clicked()
{
    double scale = 1.2;

    int tab = ui->tabWidget->currentIndex();
    switch (tab) {
    case (0): {
        QPixmap temp(DataManager::getImageName(DataManager::start_image));
        scaleFactors[0] *= scale;
        if (scaleFactors[0] > 4)
            scaleFactors[0] = 4;
        ui->start_image->setPixmap(temp.scaled(width * scaleFactors[0], height * scaleFactors[0], Qt::KeepAspectRatio, Qt::SmoothTransformation));
        break;
    }
    case (1): {
        QPixmap temp(DataManager::getImageName(DataManager::dithered_image));
        scaleFactors[1] *= scale;
        if (scaleFactors[1] > 4)
            scaleFactors[1] = 4;

        ui->w_dith->setPixmap(temp.scaled(width * scaleFactors[1], height * scaleFactors[1], Qt::KeepAspectRatio, Qt::SmoothTransformation));
        break;
    }
    case (2): {
        QPixmap temp(DataManager::getImageName(DataManager::converted_image));

        // auto temp = ui->bad_image->pixmap();
        scaleFactors[2] *= scale;
        if (scaleFactors[2] > 4)
            scaleFactors[2] = 4;

        ui->bad_image->setPixmap(temp.scaled(width * scaleFactors[2], height * scaleFactors[2], Qt::KeepAspectRatio, Qt::SmoothTransformation));
        break;
    }
    }
}
void MainWindow::on_minus_clicked()
{
    double scale = 0.8;

    int tab = ui->tabWidget->currentIndex();
    switch (tab) {
    case (0): {
        QPixmap temp(DataManager::getImageName(DataManager::start_image));
        scaleFactors[0] *= scale;
        if (scaleFactors[0] < 0.4)
            scaleFactors[0] = 0.4;

        ui->start_image->setPixmap(temp.scaled(width * scaleFactors[0], height * scaleFactors[0], Qt::KeepAspectRatio, Qt::SmoothTransformation));
        break;
    }
    case (1): {
        QPixmap temp(DataManager::getImageName(DataManager::dithered_image));
        scaleFactors[1] *= scale;
        if (scaleFactors[1] < 0.4)
            scaleFactors[1] = 0.4;

        ui->w_dith->setPixmap(temp.scaled(width * scaleFactors[1], height * scaleFactors[1], Qt::KeepAspectRatio, Qt::SmoothTransformation));
        break;
    }
    case (2): {
        QPixmap temp(DataManager::getImageName(DataManager::converted_image));
        // auto temp = ui->bad_image->pixmap();
        scaleFactors[2] *= scale;
        if (scaleFactors[2] < 0.4)
            scaleFactors[2] = 0.4;
        //ui->bad_image->resize(width * scaleFactors[2],height * scaleFactors[2]);
        ui->bad_image->setPixmap(temp.scaled(width * scaleFactors[2], height * scaleFactors[2], Qt::KeepAspectRatio, Qt::SmoothTransformation));
        break;
    }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    auto dither = currentDither();
    int result = mainManager.benchmack(dither);
    QString benchmark;
    benchmark = benchmark.number(result);
    ui->textEdit->append(ui->comboBox->currentText());
    ui->textEdit->append("Benchmark(mks for dither): " + benchmark);
}
