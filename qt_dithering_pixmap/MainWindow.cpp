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
    QImage *image1;
    ui->progressBar->setValue(5);
    mainmanager.loadFile(sourceName, image1);
    mainmanager.changeDepth(4,image1);
    ui->progressBar->setValue(10);
    mainmanager.init(image1);
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
    delete image1;
}
