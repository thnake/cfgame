#ifndef MYGRAPHICSITEM_H
#define MYGRAPHICSITEM_H

#include "MyAnimation.h"

#include <QGraphicsItemGroup>
#include <QGraphicsEllipseItem>
#include <QRadialGradient>
#include <QPropertyAnimation>


/// <summary>
/// Spielsteinklasse für das Spielbrett.
/// </summary>
class Chip : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    explicit Chip(int x, int y, int w, int h, int player, QObject *parent=NULL);
    MyAnimation* animate(QPointF end, int duration,  const QEasingCurve &curve);
    int getPlayer();
    QPointF *getCenter();


private:
    int player;

};

#endif // MYGRAPHICSITEM_H
