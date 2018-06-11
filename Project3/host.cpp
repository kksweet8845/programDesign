#include "host.h"
#include <QDebug>
host::host():
    upgradeTimes(0),
    flag(false)
{
    QPixmap *p = new QPixmap(":/new/prefix1/res/host.png");
    *p = p->scaled(50,50,Qt::IgnoreAspectRatio);
    pilot = new QGraphicsPixmapItem(*p);
    this->pilot->setPos(0,0);
    this->level = new QProgressBar();
    this->level->setGeometry(this->pilot->x(),this->pilot->y()+this->pilot->pixmap().height()+20,this->pilot->pixmap().width(),15);
    this->level->setStyleSheet("color: red;"
                                 "background-color: yellow;"
                                 "width: 25px");
    this->level->setRange(0,100);
    this->level->setValue(this->ph);
    this->connect(timer,SIGNAL(timeout()),this,SLOT(checkStatus()));
    this->connect(timer,SIGNAL(timeout()),this,SLOT(ifColliding()));
}
void host::ifColliding() {
    QList<QGraphicsItem*> list = this->pilot->collidingItems();
    for(int i=0; i < list.length();++i)
    {
        upgradeItem *item = dynamic_cast<upgradeItem*>(list.at(i));
        if(item){
            qDebug() << "Wrong";
            this->status = this->status+1;
            this->pilot->scene()->removeItem(item);
            delete item;
            flag = true;
            continue;
        }
        enemyBullet *item_ = dynamic_cast<enemyBullet*>(list.at(i));
        qDebug()<<"ph-1"<<i;
        if(item_){
            this->ph = this->ph -20;
            this->level->setValue(this->ph);
            this->pilot->scene()->removeItem(item_);
            delete item_;
        }
    }

}
void host::shoot() {
    if(status ==0){
      hostbullet *b = new hostbullet;
      b->setPixmap(QPixmap(":new/prefix1/res/bone.png").scaled(50,50));
      b->setPos(this->pilot->x() + this->pilot->pixmap().width()/2 - b->pixmap().width()/2, this->pilot->y() - b->pixmap().height());
      b->connect(this->timer,SIGNAL(timeout()),b,SLOT(bulletFly()));
      b->connect(this,&host::youAreDead,b,&hostbullet::restart);
      this->pilot->scene()->addItem(static_cast<QGraphicsPixmapItem*>(b));
    } else if(status ==1) {
         for(int i=0;i<3;i++) {
             hostbullet *b = new hostbullet;
             b->setPixmap(QPixmap(":new/prefix1/res/bone.png").scaled(50,50));
             b->setPos(this->pilot->x() + this->pilot->pixmap().width()/3*i*1.5 - b->pixmap().width()/2, this->pilot->y() - b->pixmap().height());
             b->connect(this->timer,SIGNAL(timeout()),b,SLOT(bulletFly()));
             b->connect(this,&host::youAreDead,b,&hostbullet::restart);

             this->pilot->scene()->addItem(static_cast<QGraphicsPixmapItem*>(b));
         }
    } else if(status >=2) {
        for(int i=0;i<6;i++) {
            hostbullet *b = new hostbullet;
            b->setPixmap(QPixmap(":new/prefix1/res/bone.png").scaled(50,50));
            b->setPos(this->pilot->x() - 30 + this->pilot->pixmap().width()/6*i*2.5 - b->pixmap().width()/2, this->pilot->y() - b->pixmap().height());
            b->connect(this->timer,SIGNAL(timeout()),b,SLOT(bulletFly()));
            b->connect(this,&host::youAreDead,b,&hostbullet::restart);
            this->pilot->scene()->addItem(static_cast<QGraphicsPixmapItem*>(b));
        }
    }
}

void host::checkStatus() {
    if(this->status == 1 && upgradeTimes == 0 && flag) {
        this->pilot->setPixmap(QPixmap(":new/prefix1/res/host_1.png").scaled(50,50));
        this->ph = 500;
        this->level->setRange(0,500);
        this->level->setValue(this->ph);
        flag = false;
        ++upgradeTimes;
    } else if(this->status != 1 && upgradeTimes == 1 && flag){
        this->pilot->setPixmap(QPixmap(":new/prefix1/res/host_2.png").scaled(50,50));
        this->ph = 1000;
        this->level->setRange(0,1000);
        this->level->setValue(this->ph);
        flag  = false;
        ++upgradeTimes;
    } else if(this->status != 1 && upgradeTimes == 2 && flag) {
        if(this->ph+200 <= 1000) {
            this->ph = this->ph + 200;
            this->level->setValue(this->ph);
            flag = false;
        } else {
            flag = false;
        }
    }

}
void host::Up() {
    this->pilot->setPos(this->pilot->x(),this->pilot->y()-5);
    this->level->setGeometry(this->pilot->x(),this->pilot->y()+this->pilot->pixmap().height()+20,this->pilot->pixmap().width(),15);
}
void host::Down()  {
    this->pilot->setPos(this->pilot->x(),this->pilot->y()+5);
    this->level->setGeometry(this->pilot->x(),this->pilot->y()+this->pilot->pixmap().height()+20,this->pilot->pixmap().width(),15);
}
void host::Right(){
    this->pilot->setPos(this->pilot->x()+5,this->pilot->y());
    this->level->setGeometry(this->pilot->x(),this->pilot->y()+this->pilot->pixmap().height()+20,this->pilot->pixmap().width(),15);
}
void host::Left(){
    this->pilot->setPos(this->pilot->x()-5,this->pilot->y());
    this->level->setGeometry(this->pilot->x(),this->pilot->y()+this->pilot->pixmap().height()+20,this->pilot->pixmap().width(),15);
}

void host::shootRadio(){
    int i,j;
    for(i=0;i<5;++i)
        for(j=0;j<19;++j)
        {
            qreal rad = (j+1)*3.141592768/20;
            hostbullet *b = new hostbullet(rad);
            b->setPixmap(QPixmap(":new/prefix1/res/bone.png").scaled(50,50));
            b->setPos(this->pilot->x() + this->pilot->pixmap().width()/2 - b->pixmap().width(), this->pilot->y() - b->pixmap().height());
            b->connect(this->timer,SIGNAL(timeout()),b,SLOT(bulletFly_radio()));
            b->connect(this,&host::youAreDead,b,&hostbullet::restart);
            this->pilot->scene()->addItem(static_cast<QGraphicsPixmapItem*>(b));
        }
}


void host::shootSuper(){
    int i,j;
    for(i=0;i<5;++i){
        qreal slope = 2*3.14159/i;
        for(j=0;j<10;++j)
        {
            qreal rad = (j+1)*3.14159/4;
            hostbullet *b = new hostbullet(rad,this->pilot->x(),this->pilot->y(),slope);
            b->setPixmap(QPixmap(":new/prefix1/res/bone.png").scaled(50,50));
            b->setPos(this->pilot->x() + this->pilot->pixmap().width()/2 - b->pixmap().width()/2,this->pilot->y() + this->pilot->pixmap().height()/2 - b->pixmap().height());
            b->connect(this->timer,&QTimer::timeout,b,&hostbullet::bulletFly_super);
            b->connect(this,&host::youAreDead,b,&hostbullet::restart);
            this->pilot->scene()->addItem(static_cast<QGraphicsPixmapItem*>(b));
        }
    }
}

void host::restart(){
    emit youAreDead();
}


















