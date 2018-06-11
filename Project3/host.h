#ifndef HOST_H
#define HOST_H

#include "airplain.h"
#include "upgradeitem.h"
#include "enemybullet.h"
#include "hostbullet.h"
class host : public airplain
{

    Q_OBJECT
public:
    host();

    int upgradeTimes;
    bool flag;
signals:
    void youAreDead();
public slots:
    void ifColliding();
    void checkStatus();
    void shoot();
    void shootRadio();
    void shootSuper();
    void Up();
    void Down();
    void Right();
    void Left();
    void restart();
};


#endif // HOST_H
