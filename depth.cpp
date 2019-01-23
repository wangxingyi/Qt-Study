#include "depth.h"

depth::depth(int xMax, int yMax,int xMin,int yMin,QVector<QVector<int>> v)
{
    this->xMax = xMax;
    this->yMax = yMax;
    this->xMin = xMin;
    this->yMin = yMin;
    this->v = v;
}

bool depth::ifBorder(int x, int y)
{
    return (x>xMax)&&(x<xMin)&&(y>yMax)&&(y<xMin);
}

bool depth::run(int x, int y)
{
    if(ifBorder(x,y) == false){
        if(search(x,y))
            run(x,y+1);
        else
            run(x-1,y);
    }
    if(x >= xMin){

    }
    if(x <= xMax){

    }
}

bool depth::search(int x, int y)
{
    if(v[x][y] == 0)
        return true;
    return false;
}

