#include "maze.h"
const int maze::dir[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
maze::maze(QObject *parent,int bitch) : QObject(parent),bitch(bitch)
{
    data.clear();
    qsrand(static_cast<uint>(QTime::currentTime().msec()));

}

bool maze::go(int x, int y)
{
    if(!isArea(x,y))return false;
    visited[x][y] = true;
    setData(x,y,true);
    if(x == xEnd && y == yEnd)return true;
    for(int i = 0; i < 4; i++)
    {
        int newX = x+dir[i][0];
        int newY = y+dir[i][1];
        if(isArea(newX,newY) && !visited[newX][newY] && maz[newX][newY]){

            if(go(newX,newY))return true;
        }
    }
    setData(x,y,false);
    return false;
}

void maze::go()
{
    QStack<QPair<int,int>> stack;
    QPair<int,int> first(xOrigin,yOrigin);
    stack.push(first);
    visited[xOrigin][yOrigin] = true;
    while(!stack.empty()){
        QPair<int,int> curPos = stack.pop();
        setData(curPos.first,curPos.second,true);

        if(curPos.first == xEnd && curPos.second == yEnd)
            break;

        for(int i = 0; i<4;i++){
            int newX = curPos.first+dir[i][0];
            int newY = curPos.second+dir[i][1];
            if(isArea(newX,newY) && !visited[newX][newY] && maz[newX][newY]){
                stack.push(QPair<int,int>(newX,newY));
                visited[newX][newY] = true;
            }
        }
    }
}

void maze::randGo(int x, int y)
{
//    QTimer::singleShot(1000,this,&maze::setData);
    if(!isArea(x,y))return ;
    visited[x][y] = true;
    openDense(x,y);
    for(int i =0; i<10;i++){
        int rand = (qrand() + QTime::currentTime().msec())% 4;
        int newX = x+dir[rand][0]*2;
        int newY = y+dir[rand][1]*2;
        if(isArea(newX,newY) && !visited[newX][newY]){
            setData(x+dir[rand][0],y+dir[rand][1]);
//            openDense(newX,newY);
            randGo(newX,newY);
        }
    }

}

void maze::randGo()
{
    //QStack<QPair<int,int>> stack;
    QVector<QPair<int,int>>& stack = data;
    QPair<int,int> first(xOrigin,yOrigin+1);
    Add(first);
    openDense(xOrigin,yOrigin+1);
    visited[xOrigin][yOrigin+1] = true;
    while(!stack.empty()){
        QPair<int,int> curPos = Remove();
        for(int i = 0; i<4;i++){
            int newX = curPos.first+dir[i][0]*2;
            int newY = curPos.second+dir[i][1]*2;
            if(isArea(newX,newY) && !visited[newX][newY]){
                Add(QPair<int,int>(newX,newY));
                visited[newX][newY] = true;
                openDense(newX,newY);
                setData(curPos.first + dir[i][0],curPos.second+dir[i][1]);
            }
        }
    }
}

void maze::WrandGo()
{
    QQueue<QPair<int,int>> queue;
    QPair<int,int> first(xOrigin,yOrigin+1);
    queue.enqueue(first);
    visited[xOrigin][yOrigin+1] = true;
    while(!queue.empty()){
        QPair<int,int> curPos = queue.dequeue();
        for(int i = 0; i<10;i++){
            int rand = (qrand() + QTime::currentTime().msec())% 4;
            int newX = curPos.first+dir[rand][0]*2;
            int newY = curPos.second+dir[rand][1]*2;
            if(isArea(newX,newY) && !visited[newX][newY]){
                queue.enqueue(QPair<int,int>(newX,newY));
                visited[newX][newY] = true;
                setData(curPos.first + dir[i][0],curPos.second+dir[i][1]);
            }
        }
    }
}

void maze::WrandFind()
{
    static int d[][2] = {{-1,0},{0,1},{1,0},{0,-1}};
    QQueue<QPair<int,int>> queue;
    QPair<int,int> first(xOrigin,yOrigin);
    queue.enqueue(first);
    visited[xOrigin][yOrigin] = true;
    setData(xOrigin,yOrigin,true);
    while(!queue.empty()){
        QPair<int,int> curPos = queue.dequeue();

        if(curPos.first == xEnd && curPos.second == yEnd)
            break;

        for(int i = 0; i<4;i++){
            int newX = curPos.first+d[i][0];
            int newY = curPos.second+d[i][1];
            if(isArea(newX,newY) && !visited[newX][newY] && maz[newX][newY]){
                queue.enqueue(QPair<int,int>(newX,newY));
                visited[newX][newY] = true;
                setData(newX,newY,true);
            }
        }
    }
}

bool maze::isArea(int x, int y)
{
    return x>= 0 && x<Height && y>= 0 && y< Width;
}

void maze::setData(int x,int y)
{
    if(isArea(x,y))
    {
        maz[x][y] = true;
    }
    emit mysignal();
    QThread::msleep(10);
}

void maze::setData(int x, int y, bool isPath)
{
    if(isArea(x,y)){
        path[x][y] = isPath;
    }
    emit mysignal();
    QThread::msleep(5);
}

void maze::setPtr(int Height , int Width, bool **&v, bool **&p, bool **&m, bool **&d)
{
    this->Height = Height;
    this->Width = Width;

    this->xOrigin = 1;
    this->yOrigin = 0;
    this->xEnd = Height - 2;
    this->yEnd = Width - 1;

    this->path = new bool*[Height];
    this->visited = new bool*[Height];
    this->maz = new bool *[Height];
    this->Dense = new bool *[Height];

    for(int i = 0; i < Height; i++){
        this->path[i] = new bool [Width];
        this->visited[i] = new bool [Width];
        this->maz[i] = new bool [Width];
        this->Dense[i] = new bool [Width];
    }
    for(int i = 0;i < Height; i++){
        for(int j = 0; j< Width; j++){
            if(i == 0 || i == Height - 1)
                this->visited[i][j] = true;
            else
                this->visited[i][j] = false;
            if(j == 0 || j == Height - 1)
                this->visited[i][j] = true;
            else
                this->visited[i][j] = false;
            if(i%2 == 1 && j%2 == 1)
                this->maz[i][j] = true;//路
            else
                this->maz[i][j] = false;//墙
            this->path[i][j] = false;//墙
            Dense[i][j] = true; //迷雾
        }
    }
    this->maz[xOrigin][yOrigin] = true;
    this->maz[xEnd][yEnd] = true;
    p = this->path;
    v = this->visited;
    m = this->maz;
    d = this->Dense;
    setData(-1,-1);
}

void maze::hand()
{
    randGo(1,1);
//    WrandGo();
//    randGo();
    for(int i = 0;i < Height; i++){
        for(int j = 0; j< Width; j++){
            if(i == 0 || i == Height - 1)
                this->visited[i][j] = true;
            else
                this->visited[i][j] = false;
            if(j == 0 || j == Height - 1)
                this->visited[i][j] = true;
            else
                this->visited[i][j] = false;
        }
    }
    visited[xEnd][yEnd] = false;

    go(1,0);
    //go();
//    WrandFind();
}

void maze::Add(QPair<int, int> e)
{
    if(qrand()%1001 > 500)
        data.push_back(e);
    else
        data.push_front(e);
}

QPair<int, int> maze::Remove()
{
    if(data.size() == 0)
        throw "data.size() == 0";
//    int randIndex = rand() % data.size();
//    QPair<int, int> randElement = data.at(randIndex);
//    if(qrand() % 101 > 50){
//        data.replace(randIndex,data.at(data.size() - 1));
//        data.removeLast();
//    }else{
//        data.replace(randIndex,data.at(0));
//        data.removeFirst();
//    }

//    return randElement;
    if(qrand() % 101 < 50){
        return data.takeFirst();
    }else{
        return data.takeLast();
    }
}

void maze::openDense(int x, int y)
{
    if(isArea(x,y)){
        for(int i = x - 1; i <= x+1 && i<Height; i ++){
            for(int j = y - 1; j <= y+1 && j<Width; j++){
                Dense[i][j] = false;
            }
        }
    }
}
