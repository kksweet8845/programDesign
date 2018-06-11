#include "hostbullet.h"

hostbullet::hostbullet() {

}
hostbullet::hostbullet(qreal rad):
           slope(rad),
           r(10)
{

}

hostbullet::hostbullet(qreal rad, qreal x, qreal y,qreal dir):
           slope(rad),
           r(100),
           inix(x),
           iniy(y),
           inirad(rad),
           direction(dir)
{

}


void hostbullet::bulletFly() {

        setPos(x(),y()-10);
        if(y() < -500) {
            this->scene()->removeItem(this);
            delete this;
        }
}

void hostbullet::bulletFly_radio() {

    setPos(x()+10*qCos(slope),y()-10*qSin(slope));
    if(y() < -250) {
        this->scene()->removeItem(this);
        delete this;
    }

}
void hostbullet::bulletFly_super() {
        setPos(inix+100*qSin(r)*qCos(slope),iniy+100*qSin(r)*qSin(slope));
        slope = slope +3.14159/180;
        r = r+0.1;
        inix = inix + 10*qCos(direction);
        iniy = iniy -10;
        if(y() < -250) {
            this->scene()->removeItem(this);
            delete this;
        }

}

void hostbullet::ifColliding(){
    QList<QGraphicsItem*> list = this->collidingItems();
    for(int i=0; i < list.length();++i)
    {
        QGraphicsItem *item = list.at(i);
        if(item){

        }
    }
}

void hostbullet::restart(){
    this->scene()->removeItem(this);
    delete this;
}
