#ifndef MAZE_H
#define MAZE_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QThread>
#include <QStack>
#include <QPair>
#include <QQueue>
#include <QTime>
class maze : public QObject
{
    Q_OBJECT
public:
    explicit maze(QObject *parent = nullptr,int bitch = 0);
    bool go(int x,int y);
    void go();
    void randGo(int x,int y);
    void randGo();
    void WrandGo();
    void WrandFind();
    void serXY(int xOrigin,int yOrigin,int xEnd,int yEnd);
    bool isArea(int x,int y);
    void setData(int x,int y);
    void setData(int x,int y,bool isPath);
    bool getMaze(int x,int y);
    void setPtr(int Height ,int Width,bool** &v,bool** &p,bool **&m,bool **&d);
    void hand(void);
    void Add(QPair<int,int> e);
    QPair<int,int> Remove();
    void openDense(int x,int y);
private:
    int Height,Width;   //迷宫的长宽
    int xOrigin,yOrigin;//迷宫的起始坐标
    int xEnd,yEnd;      //迷宫的终点坐标
    bool ** visited;
    bool ** path;
    bool ** maz;
    bool ** Dense;
    static const int dir[4][2];
    const int bitch;
    bool Flag;
    QVector<QPair<int,int>> data;
signals:
    void mysignal();
public slots:
};


#endif // MAZE_H
