#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include "bullet.h"
#include "hostbullet.h"

class enemyBullet : public bullet
{
    Q_OBJECT
public:
    enemyBullet();

public slots:
    void bulletFly();
    void ifColliding();
    void restart();
};
#endif // ENEMYBULLET_H
