#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QtMath>
#include <QList>
class bullet :public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    bullet () ;

public slots:
     virtual void bulletFly();
     virtual void bulletFly_radio();
     virtual void bulletFly_super();
     virtual void ifColliding();

};
#endif // BULLET_H
