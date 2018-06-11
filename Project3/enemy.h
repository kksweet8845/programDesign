#ifndef ENEMY_H
#define ENEMY_H

#include "airplain.h"
#include "enemybullet.h"
#include "hostbullet.h"
#include <QKeyEvent>
class enemy : public airplain
{
    Q_OBJECT
public:
    enemy();
    enemy(qreal x,qreal y);

    enemyBullet *b;
    qreal times;
    qreal inix;
    qreal iniy;
    qreal staytimes;
signals:
    void iAmDead();

public slots:
    void fly();
    void shoot();
    void control();
    void ifColliding();
    void restart();
};

#endif // ENEMY_H
