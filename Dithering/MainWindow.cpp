#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <QPixmap>

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

void MainWindow::on_pushButton_2_clicked()
{
    QString sourceName = QFileDialog::getOpenFileName(this, QString::fromUtf8("Открыть файл"),
        QDir::currentPath(), "images (*.*)");
    if (!sourceName.isEmpty()) {
        mainManager.loadImage(sourceName);
    }
    QPixmap temp(DataManager::getImageName(DataManager::start_image));
    ui->start_image->setPixmap(temp);

}

void MainWindow::on_pushButton_clicked()
{
    /* enum kind_dither {
        white_noise,
        blue_noise,
        brown_noise,
        red_noise,
        violet_noise
        floyd_sd
    };*/
    int index = ui->comboBox->currentIndex();
    DitherManager::kind_dither kindDither;
    switch(index){
    case 0:{
        kindDither = DitherManager::white_noise;
        break;
    }
    case 1:{
        kindDither = DitherManager::blue_noise;
        break;
    }
    case 2:{
        kindDither = DitherManager::brown_noise;
        break;
    }
    case 3:{
        kindDither = DitherManager::violet_noise;
        break;
    }
    case 4:{
        kindDither = DitherManager::pink_noise;
        break;
    }
    case 5:{
        kindDither = DitherManager::floyd_sd;
        break;
    }
    default:
        kindDither = DitherManager::white_noise;
    }

    mainManager.dither(kindDither);
    QPixmap temp(DataManager::getImageName(DataManager::dithered_image));
    ui->wo_dith->setPixmap(temp);
    QString psnr;
    psnr = psnr.number(mainManager.getMetrics(MetricsManager::psnr));
    ui->textEdit->append(ui->comboBox->currentText());
    ui->textEdit->append("PSNR: "+ psnr);
}
