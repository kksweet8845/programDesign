#include "bullet.h"

bullet:: bullet(){

}

void bullet::bulletFly() {

    setPos(x(),y()-10);
    if(y() < 0) {
        this->scene()->removeItem(this);
        delete this;
    }
}

void bullet::bulletFly_radio() {

}

void bullet::bulletFly_super(){

}

void bullet::ifColliding() {
    return;
}
