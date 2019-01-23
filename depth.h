#ifndef DEPTH_H
#define DEPTH_H
#include <QVector>

class depth
{
public:
    depth(int xMax, int yMax,int xMin,int yMin,QVector<QVector<int>> v);
    bool ifBorder(int x,int y);
    bool run(int x,int y);
    bool search(int x,int y);

private:
    int xMax,yMax;
    int xMin,yMin;
    QVector<QVector<int>>& v;
};

#endif // DEPTH_H
