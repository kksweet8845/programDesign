#ifndef HOSTBULLET_H
#define HOSTBULLET_H

#include "bullet.h"

class hostbullet : public bullet
{
public:
    hostbullet();
    hostbullet(qreal rad);
    hostbullet(qreal rad,qreal x,qreal y,qreal dir);

    qreal slope;
    qreal r;
    qreal inix,iniy;
    qreal inirad;
    qreal direction;
public slots:
    void bulletFly();
    void bulletFly_radio();
    void bulletFly_super();
    void ifColliding();
    void timing();
    void restart();
};


#endif // HOSTBULLET_H
