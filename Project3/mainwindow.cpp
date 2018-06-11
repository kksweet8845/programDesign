#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(0,0,1201,871)),
    timer(new QTimer),
    skill(new QTimer),
    times(0),
    score(0)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    player = new host;
    scene->addItem(player->pilot);
    scene->addWidget(player->level);
    timer->start(10);
    ui->score->setDigitCount(10);
    ui->score->display(0);
    ui->phBar->setRange(0,1000);
    ui->phBar->setValue(player->ph);
    connect(player->level,&QProgressBar::valueChanged,ui->phBar,&QProgressBar::setValue);
    connect(this,&MainWindow::youAreDead,player,&host::restart);
    connect(timer,SIGNAL(timeout()),this,SLOT(tempo()));
    connect(ui->Radio,&QPushButton::clicked,this,&MainWindow::radioSkill);
    connect(ui->Super,&QPushButton::clicked,this,&MainWindow::superSkill);
    connect(ui->restart,&QPushButton::clicked,this,&MainWindow::restart);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
    switch(e->key()) {
    case Qt::Key_Up:
    case Qt::Key_W:
        connect(timer,SIGNAL(timeout()),player,SLOT(Up()));
        break;
    case Qt::Key_Down:
    case Qt::Key_S:
        connect(timer,SIGNAL(timeout()),player,SLOT(Down()));
        break;
    case Qt::Key_Right:
    case Qt::Key_D:
        connect(timer,SIGNAL(timeout()),player,SLOT(Right()));
        break;
    case Qt::Key_Left:
    case Qt::Key_A:
        connect(timer,SIGNAL(timeout()),player,SLOT(Left()));
        break;
    case Qt::Key_N:
    case Qt::Key_Z:
        break;
    }

}
void MainWindow::keyReleaseEvent(QKeyEvent *e){
    switch (e->key()) {
    case Qt::Key_W:
        disconnect(timer,SIGNAL(timeout()),player,SLOT(Up()));
        break;
    case Qt::Key_S:
        disconnect(timer,SIGNAL(timeout()),player,SLOT(Down()));
        break;
    case Qt::Key_D:
        disconnect(timer,SIGNAL(timeout()),player,SLOT(Right()));
        break;
    case Qt::Key_A:
        disconnect(timer,SIGNAL(timeout()),player,SLOT(Left()));
        break;
    default:
        break;
    }
}
void MainWindow::mousePressEvent(QMouseEvent *e){
        player->shoot();
}
void MainWindow::showEnemy() {
    QTime times = QTime::currentTime();
    qsrand((uint)times.msec());

    qreal dx = qrand()%1000+25;
    qreal dy = -1000;
    if(scene->itemAt(dx,dy,QTransform()) == 0) {
        enemy *e = new enemy(dx,dy);
        connect(e,&enemy::iAmDead,this,&MainWindow::scoreNumber);
        scene->addItem(e->pilot);
        scene->addWidget(e->level);
        e->connect(timer,SIGNAL(timeout()),e,SLOT(fly()));
        e->connect(timer,SIGNAL(timeout()),e,SLOT(ifColliding()));
        e->connect(this,&MainWindow::youAreDead,e,&enemy::restart);
    }else
        showEnemy();
}
void MainWindow::tempo() {
    //enemy
    switch(times){
    case 0:
        for(int i=0;i<8;++i)
        showEnemy();
        showUpgradeItem();
        ++times;
        break;
    case 100:
        for(int i =0;i<8;++i)
        showEnemy();
        ++times;
        break;
    case 200:
        showUpgradeItem();
        ++times;
        break;
    case 300:
        for(int i=0;i<3;++i)
        showEnemy();
        ++times;
        break;
    case 400:
        ++times;
        break;
    case 1500:
        disconnect(skill,&QTimer::timeout,player,&host::shootSuper);
        skill->stop();
        ++times;
        break;
    case 2000:
        disconnect(skill,&QTimer::timeout,player,&host::shootRadio);
        skill->stop();
        times = 0;
        break;
    default:
        ++times;
        break;
    }
}
void MainWindow::showUpgradeItem() {
    QTime times = QTime::currentTime();
    qsrand((uint)times.msec());
    qreal dx = qrand()%1000+25;
    qreal dy = -1000;
    upgradeItem *u  = new upgradeItem;
    u->setPos(dx,dy);
    u->connect(timer,SIGNAL(timeout()),u,SLOT(bulletFly()));
    u->connect(timer,SIGNAL(timeout()),u,SLOT(ifColliding()));
    u->connect(this,&MainWindow::youAreDead,u,&upgradeItem::restart);
    scene->addItem(static_cast<QGraphicsPixmapItem*>(u));

}
void MainWindow::radioSkill() {
    skill->start(200);
    connect(skill,&QTimer::timeout,player,&host::shootRadio);
}

void MainWindow::phBar() {
    ui->phBar = player->level;
}

void MainWindow::scoreNumber(){
    this->score = this->score + 500;
    ui->score->display(this->score);
}

void MainWindow::superSkill(){
    skill->start(100);
    connect(skill,&QTimer::timeout,player,&host::shootSuper);
}
void MainWindow::restart(){
    ui->score->display(0);
    player->level->setRange(0,100);
    player->level->setValue(100);
    player->pilot->setPixmap(QPixmap(":new/prefix1/res/host.png").scaled(50,50));
    emit youAreDead();
}
