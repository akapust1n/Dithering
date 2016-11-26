#ifndef MAINMANAGER_H
#define MAINMANAGER_H
#include <QImage>
#include "DataManager.h"
#include <QString>
class MainManager
{
public:
    void loadImage(QString filename);
private:
    DataManager dataManager;
};

#endif // MAINMANAGER_H
