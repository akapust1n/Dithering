#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "MainManager.h"
#include <thread>
#include <mutex>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
    void on_convert_end();
signals:
    void convert_end();
private:
    Ui::MainWindow *ui;
    MainManager mainManager;
    void convert();
    std::mutex _mutex;
};

#endif // MAINWINDOW_H
