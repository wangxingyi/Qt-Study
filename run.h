#ifndef RUN_H
#define RUN_H

#include <QObject>
class run :public QObject
{
    Q_OBJECT
public:
    run(int Height=101,int Width=101);
    bool go(int x,int y);
    void randGo(int x,int y);
    void serXY(int xOrigin,int yOrigin,int xEnd,int yEnd);
    bool isArea(int x,int y);
    void setData(int x,int y,bool isPath);
    bool getMaze(int x,int y);
    void setPtr(bool** v,bool** p,bool **m);


private:
    int Height,Width;   //迷宫的长宽
    int xOrigin,yOrigin;//迷宫的起始坐标
    int xEnd,yEnd;      //迷宫的终点坐标
    bool ** visited;
    bool ** path;
    bool ** maze;
    int ** dir;
signals:
    void mysignal();
};

#endif // RUN_H
