#ifndef WIDGET_H
#define WIDGET_H
#include <QPaintDevice>
#include <QPainter>
#include <QPen>
#include <QWidget>
#include "maze.h"
#include <QThread>
#include <QTimer>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void paintEvent(QPaintEvent *e);
    void Timeout(void);
private:
    Ui::Widget *ui;
    maze *r;
    int Height, Width;
    int BlockSide;
    bool ** visited;
    bool ** path;
    bool ** maz;
    bool ** Dense;
    QThread *thread;

signals:
    void widSignal(void);
};

#endif // WIDGET_H
