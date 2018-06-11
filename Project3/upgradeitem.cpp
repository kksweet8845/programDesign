#include "upgradeitem.h"
#include <QDebug>
upgradeItem::upgradeItem():sign(false) {

    this->setPixmap(QPixmap(":new/prefix1/res/dogfood.png").scaled(50,50));
}


void upgradeItem::ifColliding() {

    QList<QGraphicsItem*> list = this->collidingItems();

    for(int i=0; i < list.length();++i)
    {
        QGraphicsPixmapItem *item = dynamic_cast<QGraphicsPixmapItem*>(list.at(i));
        if(item){
            sign = true;
            return;
        }
    }
}

void upgradeItem::bulletFly() {
    setPos(x(),y()+1);
    if(y() > 871) {
        if(!sign)
            this->scene()->removeItem(this);
        delete this;
    }
}

void upgradeItem::restart(){
    this->scene()->removeItem(this);
    delete this;
}
