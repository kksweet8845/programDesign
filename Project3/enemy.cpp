#include "enemy.h"

enemy::enemy():
    times(0),
    inix(0),
    staytimes(0)
{
    pilot = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/res/enemy.png"));
    connect(timer,SIGNAL(timeout()),this,SLOT(control()));
}
enemy::enemy(qreal x,qreal y):
    times(0),
    inix(x),
    staytimes(0)
{
    pilot = new QGraphicsPixmapItem(QPixmap(":/new/prefix1/res/enemy.png").scaled(50,50));
    this->pilot->setPos(x,y);
    this->level = new QProgressBar();
    this->level->setStyleSheet("color: red;"
                               "background-color: transparent;");
    this->level->setGeometry(this->pilot->x(),this->pilot->y()+this->pilot->pixmap().height()+20,this->pilot->pixmap().width(),15);
    this->level->setRange(0,100);
    this->level->setValue(this->ph);
    connect(timer,SIGNAL(timeout()),this,SLOT(control()));
    connect(timer,SIGNAL(timeout()),this,SLOT(ifColliding()));
}
void enemy::fly(){
    qreal dy;
    dy = this->pilot->y();
    if(staytimes == 0 && dy <= -5 ){
        this->pilot->setPos(inix+50*qCos(dy*3.14159/100),dy+2);
        this->level->setGeometry(this->pilot->x(),this->pilot->y()+this->pilot->pixmap().height()+20,this->pilot->pixmap().width(),15);
    } else if(staytimes >= 500 && dy >=-5) {
        this->pilot->setPos(inix+50*qCos(dy*3.14159/100),dy+2);
        this->level->setGeometry(this->pilot->x(),this->pilot->y()+this->pilot->pixmap().height()+20,this->pilot->pixmap().width(),15);
        if(this->pilot->y() >871) {
            this->pilot->scene()->removeItem(this->pilot);
            delete this;
            return;
        }
        disconnect(timer,SIGNAL(timeout()),this,SLOT(control()));
    } else if(staytimes <= 499 ) {
        ++staytimes;
        this->pilot->setPos(inix+50*qCos(staytimes*3.14159/100),dy);
    }
}
void enemy::shoot() {
    enemyBullet *b = new enemyBullet;

    b->setPixmap(QPixmap(":/new/prefix1/res/enemybullet.png").scaled(25,25));
    b->setPos(this->pilot->x() + this->pilot->pixmap().width()/2 - b->pixmap().width(), this->pilot->y() + b->pixmap().height());
    b->connect(timer,SIGNAL(timeout()),b,SLOT(bulletFly()));
    b->connect(timer,&QTimer::timeout,b,&enemyBullet::ifColliding);
    this->pilot->scene()->addItem(static_cast<QGraphicsPixmapItem*>(b));


}

void enemy::control() {

    if(times == 60)
    {
        ++times;
    } else if(times == 70){
        ++times;
    } else if(times == 80) {
        shoot();
        times = 0;
    } else {
        ++times;
    }

}
void enemy::ifColliding() {

    QList<QGraphicsItem*> list = this->pilot->collidingItems();

    for(int i=0; i < list.length();++i)
    {
        hostbullet *item = dynamic_cast<hostbullet*>(list.at(i));
        if(item){
            if(this->ph == 0)
            {
                this->pilot->scene()->removeItem(this->pilot);
                emit iAmDead();
                delete this->level;
                delete this;

                return;
            }
            this->ph = this->ph -1;
            this->level->setValue(this->ph);
        }
    }
}

void enemy::restart(){
    this->pilot->scene()->removeItem(this->pilot);
    delete this->level;
    delete this;
}


