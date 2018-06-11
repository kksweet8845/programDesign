#ifndef AIRPLAIN_H
#define AIRPLAIN_H


#include <QObject>
#include <QTimer>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QtMath>
#include <QProgressBar>
#include <QPalette>
#include <QList>


class airplain : public QObject
{
    Q_OBJECT
public:
    airplain ();


    QGraphicsPixmapItem *pilot;
    QProgressBar *level;
    int ph,status,pre_status;
    QTimer *timer;

public slots:
    virtual void ifColliding();
    virtual void checkStatus();
    virtual void shoot();

};















#endif // AIRPLAIN_H
