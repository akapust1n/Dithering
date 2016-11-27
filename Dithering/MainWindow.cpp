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
    mainManager.dither(DitherManager::white_noise);
    QPixmap temp(DataManager::getImageName(DataManager::dithered_image));
    ui->wo_dith->setPixmap(temp);
}
