#include "mouse.h"
#include <QMouseEvent>
#include <QPainter>
#include<QTimer>

Mouse::Mouse(QWidget *parent) : QAbstractButton(parent)
{
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,
            this,&Mouse::flyUpImage);
    yPos = height();
    rate = 50;
    upFlags = 0;

}

void Mouse::setBackImage(QString path, int lvl)
{
    img.load(path);
    if(path.isEmpty())
    {
        timer->stop();
        yPos = 0;
        this->upFlags;
        yPos = height();
        upFlags = 0;
        return;

    }
    switch(lvl){
    case 1:rate = 25;break;
    case 2:rate = 15;break;
    case 3:rate = 10;break;
    default: rate = 45;break;
    }
    timer->start(rate);
}

void Mouse::flyUpImage()
{
    if(yPos <= 0)
    {
        upFlags = 1;
    }
    else if (yPos >= height()) {
        upFlags = 0;
    }
    if(upFlags == 0)
    {
        yPos -= 5;
    }
    else {
        yPos +=5;
    }
    update();
}

void Mouse::mousePressEvent(QMouseEvent *e)
{
    click();
    e->ignore();
}

void Mouse::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRect source(0,0,img.width(),img.height());
    QRect target(0,yPos,width(),height());
    painter.drawImage(target,img,source);
}
