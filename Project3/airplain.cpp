#include "airplain.h"


airplain::airplain():
    ph(100),
    status(0),
    pre_status(0),
    timer(new QTimer)
{
    this->timer->start(10);
}



void airplain::ifColliding() {
    return;
}

void airplain::checkStatus(){
    return;
}

void airplain::shoot() {
    return;
}
