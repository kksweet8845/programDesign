#ifndef UPGRADEITEM_H
#define UPGRADEITEM_H

#include <QObject>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QtMath>
#include <QProgressBar>
#include <QPalette>
#include <QList>
#include "airplain.h"
#include "host.h"
#include "bullet.h"

class upgradeItem : public bullet
{
    Q_OBJECT
public:
    upgradeItem();

    bool sign;
public slots:
    void ifColliding();
    void bulletFly();
    void restart();
};

#endif // UPGRADEITEM_H
