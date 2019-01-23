#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    Height = 49;
    Width = 49;
    BlockSide = 10;

    setGeometry(0,0,Width*BlockSide,Height*BlockSide);

    visited = nullptr;
    path = nullptr;
    maz =nullptr;
    r = new maze;
    thread = new QThread(this);

    r->setPtr(Height,Width,visited,path,maz,Dense);

    connect(this,&Widget::widSignal,r,&maze::hand);
    connect(r,&maze::mysignal,[=](){
        update();
    });

    r->moveToThread(thread);
    thread->start();
    Timeout();
}

Widget::~Widget()
{
    thread->quit();
    thread->wait();
    delete ui;
}
void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter;
    if(path == nullptr || visited == nullptr || maz == nullptr){
        return;
    }
    painter.begin(this);
    for(int i = 0; i < Height; i++){
        for(int j = 0; j < Width; j++){
            QRect r(QPoint(i*BlockSide,j*BlockSide),
                    QPoint((i+1)*BlockSide,(j+1)*BlockSide));
            if(Dense[i][j])
                painter.fillRect(r,Qt::black);
            else if(maz[i][j] == false)
                painter.fillRect(r,Qt::green);
            else
                painter.fillRect(r,Qt::white);
            if(path[i][j])
                painter.fillRect(r,Qt::red);
        }
    }
    painter.end();

}

void Widget::Timeout()
{
    //QTimer::singleShot(500,this,&Widget::Timeout);
    emit widSignal();
}
