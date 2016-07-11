#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    string sourceName = QFileDialog::getOpenFileName(this, QString::fromUtf8("Открыть файл"),
                            QDir::currentPath(), "images (*.*)")
                            .toStdString();
}
