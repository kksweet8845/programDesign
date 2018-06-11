#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTimer>
#include <QTime>
#include <QTableWidgetItem>

namespace Ui {
class MainWindow;

}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void generate();
    void answer();
    void rand_(int num);
    bool valid();
    void backtrack(int x,int y);
    void print();
    void input();
    void asign();
    void remove();
    void ini();
    void ini_interface();
    void ini_time();


    int e;
    int board[9][9];
    int check_num;
    int time;
public slots:
    void Generate();
    void Answer();
    void Remove();
    void Undo();
    void Sync(int x,int y);
    void Hint();
    void Start();
    void Start_timer();
    void Stop();
    void Clear();

private:
    Ui::MainWindow *ui;
    bool dx[9][10];
    bool dy[9][10];
    bool grid[10][3][3];
    bool pre[9][9];
    int order[500][3];
    int ans[9][9];
    bool cus_pre[9][9];
    QTimer *sudoku_time;
    QTableWidgetItem *preitem,*newitem;


private slots:
    void ShowTime();

};

#endif // MAINWINDOW_H
