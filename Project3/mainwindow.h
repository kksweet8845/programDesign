#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "bullet.h"
#include "airplain.h"
#include "enemy.h"
#include "host.h"
#include "hostbullet.h"
#include "enemybullet.h"
#include <QKeyEvent>
#include <QTime>
#include <QColor>
#include <QTransform>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void youAreDead();
public slots:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void keyReleaseEvent(QKeyEvent *e);
    void showEnemy();
    void tempo();
    void showUpgradeItem();
    void radioSkill();
    void phBar();
    void scoreNumber();
    void superSkill();
    void restart();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    host *player;
    QTimer *timer,*skill;
    int times;
    int score;
};

#endif // MAINWINDOW_H
