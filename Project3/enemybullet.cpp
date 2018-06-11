#include "enemybullet.h"

enemyBullet::enemyBullet() {

}

void enemyBullet::bulletFly() {
    setPos(x(),y()+3);
    if(y() > 1200) {
        this->scene()->removeItem(this);
        delete this;
    }
}

void enemyBullet::ifColliding(){
    QList<QGraphicsItem*> list = this->collidingItems();
    for(int i=0; i < list.length();++i)
    {
        hostbullet *item_ = dynamic_cast<hostbullet*>(list.at(i));
        if(item_){
            this->scene()->removeItem(this);
            delete this;
            return;
        }
    }
}

void enemyBullet::restart(){
    this->scene()->removeItem(this);
    delete this;
}
