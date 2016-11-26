#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>

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
}
