#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QTime>
#include <QString>
#include <QColor>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(54.2);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(54.2);
    e = 0;
    check_num=0;
    memset(board,0,sizeof(board));
    memset(dx,0,sizeof(dx));
    memset(dy,0,sizeof(dy));
    memset(grid,0,sizeof(grid));
    memset(pre,1,sizeof(pre));
    memset(order,0,sizeof(order));
    memset(cus_pre,0,sizeof(cus_pre));

    connect(ui->pushButton_gen,&QPushButton::clicked,this,&MainWindow::Generate);
    connect(ui->pushButton_answer,&QPushButton::clicked,this,&MainWindow::Answer);
    connect(ui->pushButton_clear,&QPushButton::clicked,this,&MainWindow::Remove);
    connect(ui->tableWidget,SIGNAL(cellChanged(int,int)),this,SLOT(Sync(int,int)));
    connect(ui->pushButton_undo,&QPushButton::clicked,this,&MainWindow::Undo);
    connect(ui->pushButton_hint,&QPushButton::clicked,this,&MainWindow::Hint);
    connect(ui->pushButton_start,&QPushButton::clicked,this,&MainWindow::Start);
    connect(ui->pushButton_gen,&QPushButton::clicked,this,&MainWindow::Start_timer);
    connect(ui->pushButton_finish,&QPushButton::clicked,this,&MainWindow::Stop);
    connect(ui->pushButton_rem,&QPushButton::clicked,this,&MainWindow::Clear);
    //connect(ui->pushButton_cus,&QPushButton::clicked,this,&MainWindow::Custom);
    ini_interface();


}
void MainWindow::ini_interface(){
    ui->tableWidget->hide();
    ui->label->hide();
    ui->pushButton_answer->hide();
    ui->pushButton_clear->hide();
    ui->pushButton_gen->hide();
    ui->pushButton_hint->hide();
    ui->pushButton_undo->hide();
    ui->pushButton_finish->hide();
    ui->lcdNumber->hide();
    ui->label_con->hide();
    ui->label_try->hide();
    ui->label_sec->hide();
    ui->label_time->hide();
    ui->pushButton_rem->hide();
    //ui->pushButton_cus->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::ini_time(){

    sudoku_time = new QTimer(this);
    ui->lcdNumber->setDigitCount(4);

    sudoku_time->start(1000);
    connect(sudoku_time,&QTimer::timeout,this,&MainWindow::ShowTime);
}


void MainWindow::generate(){

    rand_(54);
}
void MainWindow::answer(){
    backtrack(0,0);
}
void MainWindow::ini(){
    e = 0;
    check_num = 0;
    memset(board,0,sizeof(board));
    memset(dx,0,sizeof(dx));
    memset(dy,0,sizeof(dy));
    memset(grid,0,sizeof(grid));
    memset(pre,1,sizeof(pre));
    memset(order,0,sizeof(order));
    memset(cus_pre,0,sizeof(cus_pre));
}
void MainWindow::rand_(int num){
    int rand_num;
    int rand_x,rand_y;
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    ini();
            for(int j=0;j<9;j++)
            {
                    rand_num = qrand()%9+1;
                    if( board[0][j]==0 && !dx[0][rand_num] && !dy[j][rand_num] && !grid[rand_num][0][j/3])
                    {
                            board[0][j] = rand_num;

                            dx[0][rand_num] = dy[j][rand_num] = grid[rand_num][0][j/3] = true;
                    }
                    else
                    {
                            --j;
                    }
            }
            answer();
            int n,m;
            for(n=0;n<9;n++)
                for(m=0;m<9;m++)
                    ans[n][m] = board[n][m];

            e =0;
            for(int i=1;i<=num;i++)
            {
                    rand_x = qrand()%9;
                    rand_y = qrand()%9;
                    rand_num = board[rand_x][rand_y];
                    int z=0;
                    for(int x=1;x<=9;x++)
                    {
                            if(!grid[x][rand_x/3][rand_y/3])
                                    z++;
                    }

                    if(board[rand_x][rand_y]!=0 && z<=6 )
                    {
                            dx[rand_x][rand_num] = dy[rand_y][rand_num] = grid[rand_num][rand_x/3][rand_y/3] = false;
                            board[rand_x][rand_y] = 0;
                            pre[rand_x][rand_y] = 0;
                    }
                    else
                    {
                            --i;
                    }

            }

}

bool MainWindow::valid(){
    int i,j;
           for(i=0;i<9;i++)
                   for(j=1;j<9;j++)
                   {
                           if(!dx[i][j])
                                   return 0;
                           if(!dy[i][j])
                                   return 0;
                   }
           int n;
           for(i=0;i<3;i++)
                   for(j=0;j<3;j++)
                           for(n=1;n<=9;n++)
                                   if(!grid[n][i][j])
                                           return 0;
           return 1;

}

void MainWindow::backtrack(int x, int y){
    if(y == 9) {x++;y=0;}
           if(e == 1) return;
           if(x == 9)
           {
                   if(!valid())
                   {
                   //      printf("Incorrect\n");
                           return;
                   }
                   else
                   {
                   //      printf("correct\n");
                           e = 1;
                           return;
                   }


           }
           for(int i=1;i<=9;i++)
           {
                   if(board[x][y]==0 && !dx[x][i] && !dy[y][i] && !grid[i][x/3][y/3])
                   {
                           board[x][y] = i;
                           dx[x][i] = dy[y][i] = grid[i][x/3][y/3] = true;
                           backtrack(x,y+1);
                           if(e ==1)
                           return;
                           dx[x][i] = dy[y][i] = grid[i][x/3][y/3] = false;
                           board[x][y] = 0;
                   }
                   else if(board[x][y]!=0)
                           break;

           }

           if(board[x][y]!=0)
                   backtrack(x,y+1);



}
void MainWindow::remove(){
    memset(board,0,sizeof(board));
    memset(dx,0,sizeof(dx));
    memset(dy,0,sizeof(dy));
    memset(grid,0,sizeof(grid));
    memset(order,0,sizeof(order));
    memset(pre,1,sizeof(pre));

    int i,j;
    for(i=0;i<9;++i)
        for(j=0;j<9;++j)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem(" ");
            ui->tableWidget->setItem(i,j,newItem);
        }

}

void MainWindow::Generate(){

    remove();
    generate();
    asign();
    ui->label_con->hide();
    ui->label_try->hide();
    ui->label->show();

}
void MainWindow::asign(){
    int i,j;

    for(i=0;i<9;++i)
        for(j=0;j<9;++j)
            if(board[i][j] != 0)
            {
                QTableWidgetItem *newItem = new QTableWidgetItem(QString::number(board[i][j]));
                newItem->setTextAlignment(Qt::AlignCenter);
                newItem->setBackgroundColor(QColor(0,250,212));
                if(pre[i][j] != 1)
                {
                    newItem->setBackgroundColor(Qt::white);
                }
                if(cus_pre[i][j] ==1 && pre[i][j] != 1)
                {
                    newItem->setBackgroundColor(Qt::white);
                }

                ui->tableWidget->setItem(i,j,newItem);

            }else{

                QTableWidgetItem *newItem = new QTableWidgetItem(" ");
                newItem->setTextAlignment(Qt::AlignCenter);
                newItem->setBackgroundColor(Qt::white);
                ui->tableWidget->setItem(i,j,newItem);
            }
}
void MainWindow::Answer(){


    answer();
    asign();
}
void MainWindow::Remove(){
    int i,j,num;
    e = 0;
    for(i=0;i<9;++i)
        for(j=0;j<9;++j)
             if(pre[i][j] != 1)
             {
                 QTableWidgetItem *newItem = new QTableWidgetItem(" ");
                 newItem->setTextAlignment(Qt::AlignCenter);
                 newItem->setBackgroundColor(Qt::white);
                 ui->tableWidget->setItem(i,j,newItem);
                 num = board[i][j];
                 dx[i][num] = dy[j][num] = grid[num][i/3][j/3] = false;
                 board[i][j] = 0;
             }
}
void MainWindow::Sync(int x,int y){
    int num,b_num ;
    num = ui->tableWidget->item(x,y)->text().toInt();
    b_num = board[x][y];
    order[++check_num][0] = x;
    order[check_num][1] = y;
    order[check_num][2] = board[x][y];
    qDebug() <<"check_num = "<< check_num ;
    qDebug() <<"num  = "<<num;
    if(num == 0)
    {
        dx[x][b_num] = dy[y][b_num] = grid[b_num][x/3][y/3] = false;
        board[x][y] = 0;

    }else if(num != 0)
    {
        dx[x][b_num] = dy[y][b_num] = grid[b_num][x/3][y/3] = false;
        board[x][y] = num;
        cus_pre[x][y] = true;
        dx[x][num] = dy[y][num] = grid[num][x/3][y/3] = true;
    }

}

void MainWindow::Undo(){

    int x,y,pre_num;
    if(check_num == 0)
    return;

    x = order[check_num][0];
    y = order[check_num][1];
    pre_num = order[check_num--][2];
    board[x][y] = pre_num;
    qDebug() <<"undo check_num = "<<check_num;
    if(pre_num == 0 && !pre[x][y] && !cus_pre[x][y])
    {
        QTableWidgetItem *newItem = new QTableWidgetItem(" ");
        newItem->setBackgroundColor(Qt::white);
        newItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(x,y,newItem);
    }
    else if(pre_num != 0 && !pre[x][y] && !cus_pre[x][y])
    {
        QTableWidgetItem *newItem = new QTableWidgetItem(QString::number(pre_num));
        newItem->setBackgroundColor(Qt::white);
        newItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(x,y,newItem);
    }
    else if(pre[x][y])
    {
        QTableWidgetItem *newItem = new QTableWidgetItem(QString::number(pre_num));
        newItem->setBackgroundColor(QColor(0,250,212));
        newItem->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->setItem(x,y,newItem);
    }
    check_num--;



}
void MainWindow::Hint(){
    int i,j;
    for(i=0;i<9;++i)
        for(j=0;j<9;++j)
            if(pre[i][j] == 0 && board[i][j] == 0)
            {
               board[i][j] = ans[i][j];
               QTableWidgetItem *newItem = new QTableWidgetItem(QString::number(ans[i][j]));
               newItem->setBackgroundColor(Qt::white);
               newItem->setTextAlignment(Qt::AlignCenter);
               ui->tableWidget->setItem(i,j,newItem);
               check_num--;
               return;
            }


}
void MainWindow::ShowTime(){
    time++;
    ui->lcdNumber->display(time);
}
void MainWindow::Start_timer(){
    time = 0;
    ini_time();
}
void MainWindow::Stop(){
    sudoku_time->stop();
    if(valid() == 1)
    {
        ui->label->hide();
        ui->label_con->show();
    }
    else
    {
        ui->label->hide();
        ui->label_try->show();
    }


}
void MainWindow::Clear(){
    int i,j;
    for(i=0;i<9;++i)
        for(j=0;j<9;++j)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem(" ");
            newItem->setBackground(Qt::white);
            newItem->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i,j,newItem);

        }
        ini();


}

void MainWindow::Start(){
    ui->pushButton_answer->show();
    ui->pushButton_clear->show();
    ui->pushButton_gen->show();
    ui->pushButton_hint->show();
    ui->pushButton_undo->show();
    ui->label->show();
    ui->tableWidget->show();
    ui->lcdNumber->show();
    ui->pushButton_finish->show();
    ui->label_2->hide();
    ui->pushButton_start->hide();
    ui->label_sec->show();
    ui->label_time->show();
    //ui->pushButton_cus->show();
    ui->label_pro->hide();
    ui->pushButton_rem->show();

}
