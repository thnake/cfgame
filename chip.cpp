#include "chip.h"

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QRadialGradient>
#include <QGraphicsEllipseItem>
#include  <QGraphicsScene>
#include  <cstddef>

Chip::Chip(int x, int y, int w, int h, QObject *parent)
    : QObject(parent), QGraphicsEllipseItem((qreal)x,(qreal)y,(qreal)w,(qreal)h)
{

    //brush().gradient()
    setDesign();
}

void Chip::setPlayer(int p)
{

    if(p == 1)
    {
        setBrush(QBrush(Qt::black));
    }
    else if(p == 2)
    {
        setBrush(QBrush(Qt::red));
    }


}

void Chip::setGradient(QPointF p)
{
    //qradialgradient(spread:pad, cx:0.499818, cy:0.511, radius:0.5, fx:0.932374, fy:0.760791, stop:0.420455 rgba(30, 10, 36, 255), stop:1 rgba(255, 255, 255, 255))




    QRadialGradient gradient( 50, 50, 50, 20, 20 );
    gradient.setColorAt( 0.0, Qt::white );
    gradient.setColorAt( 0.7, Qt::yellow );
    gradient.setColorAt( 1.0, Qt::black );
    setBrush(gradient);

    return;
    QRadialGradient g(p, 50);
    g.setCenter(0,0);
    g.setFocalPoint(p);
    g.setColorAt(1, QColor(Qt::yellow).light(120));
    g.setColorAt(0, QColor(Qt::darkYellow).light(120));
    setBrush(g);
}


void Chip::setDesign()
{

    setPen(Qt::NoPen);
    setBrush(Qt::darkGray);

    QRadialGradient gradient(scenePos(), 100);
    if (true) {

        gradient.setCenter(0,0);
        gradient.setFocalPoint(pos());
        gradient.setColorAt(1, QColor(Qt::yellow).light(120));
        gradient.setColorAt(0, QColor(Qt::darkYellow).light(120));
    } else {
        gradient.setColorAt(0, Qt::yellow);
        gradient.setColorAt(1, Qt::darkYellow);
    }
    setBrush(gradient);

    setPen(QPen(Qt::black, 0));
    //painter->drawEllipse(-10, -10, 20, 20);
}

