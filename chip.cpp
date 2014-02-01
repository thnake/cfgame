#include "chip.h"
#include "MyAnimation.h"

#include <QAbstractAnimation>
#include <QDebug>
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QRadialGradient>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <cstddef>



Chip::Chip(int x, int y, int w, int h, int player, QObject *parent)
    : QObject(parent), QGraphicsEllipseItem((qreal)x,(qreal)y,(qreal)w,(qreal)h)
{
    this->player = player;
}


MyAnimation* Chip::animate(QPointF end, int duration,  const QEasingCurve &curve)
{
    MyAnimation* animation = new MyAnimation(this, "pos");
    animation->setDuration(duration);
    animation->setEndValue(end);
    animation->setEasingCurve(curve);
    return animation;
}


void Chip::setGradient(QPointF p)
{

return;
    gradient = QRadialGradient(QPoint(60, 60), 60, p);
    gradient.setColorAt(0.0, QColor(220, 220, 0));
    gradient.setColorAt(0.35, QColor(200, 200, 0));
    gradient.setColorAt(0.45, QColor(120, 120, 0));

    gradient.setColorAt(0.5, Qt::black);
    gradient.setColorAt(0.55, Qt::blue);
    gradient.setColorAt(1.0, Qt::green);

    setBrush(gradient);

    return;
    QRadialGradient g(p, 50);
    g.setCenter(0,0);
    g.setFocalPoint(p);
    g.setColorAt(1, QColor(Qt::yellow).light(120));
    g.setColorAt(0, QColor(Qt::darkYellow).light(120));
    setBrush(g);
}

QPointF* Chip::getCenter()
{
    QPointF *c = new QPointF();
    c->setX(pos().x() + boundingRect().width()/2);
    c->setY(pos().y() + boundingRect().width()/2);
  //  qDebug() << c->y();

    return c;
}


void Chip::setDesign()
{

    return;

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

int Chip::getPlayer()
{
    return player;
}

