#include "run.h"

run::run(int Height, int Width)
{
    this->Height = Height;
    this->Width = Width;
    this->xOrigin = 1;
    this->yOrigin = 0;
    this->xEnd = Height - 2;
    this->yEnd = Width - 1;
}

bool run::go(int x, int y)
{
    setData(x,y,true);
    if(x == xEnd && y == yEnd){
        return true;
    }
    for(int i = 4;i<4;i++){
        int newX = x,newY = y;
        switch (i) {
        case 0:newX -= 1;break;
        case 1:newY += 1;break;
        case 2:newX += 1;break;
        case 3:newY -= 1;break;
        }
        if(isArea(newX,newY) && !visited[newX][newY]){
            if(go(newX,newY))return true;
        }
    }
    setData(x,y,false);
    return false;
}

void run::randGo(int x, int y)
{
    setData(x,y,true);

    for(int i = 4;i<4;i++){
        int newX = x,newY = y;
        switch (i) {
        case 0:newX -= 1;break;
        case 1:newY += 1;break;
        case 2:newX += 1;break;
        case 3:newY -= 1;break;
        }
        if(isArea(newX,newY) && !visited[newX][newY]){

        }
    }
    setData(x,y,false);
}

void run::serXY(int xOrigin, int yOrigin, int xEnd, int yEnd)
{
    this->xOrigin = xOrigin;
    this->yOrigin = yOrigin;
    this->xEnd = xEnd;
    this->yEnd = yEnd;
}

bool run::isArea(int x, int y)
{
    return (x<=xEnd)&&(x>=xOrigin)&&(y<=yEnd)&&(y>=yOrigin);
}

void run::setData(int , int , bool)
{
    emit mysignal();
}

void run::setPtr(bool **v, bool **p,bool **m)
{
    this->path = p;
    this->visited = v;
    this->maze = m;

    this->path = new bool*[Height];
    this->visited = new bool*[Height];
    this->maze = new bool *[Height];

    for(int i = 0; i < Height; i++){
        this->path[i] = new bool [Width];
        this->visited[i] = new bool [Width];
        this->maze[i] = new bool [Width];
    }
    for(int i = 0;i < Height; i++){
        for(int j = 0; j< Width; j++){
            this->path[i][j] = false;
            this->visited[i][j] = false;
            if(i%2 == 1 && j%2 == 1)
                this->maze[i][j] = true;//路
            else
                this->maze[i][j] = false;//墙
        }
    }

    setData(-1,-1,false);
}

