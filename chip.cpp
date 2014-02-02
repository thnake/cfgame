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


/// <summary>
/// Konstruktor der Klasse Chip. Erstellt einen Spielstein für Vier Gewinnt
/// </summary>
/// <param name="x">x Position des bounding rect</param>
/// <param name="y">x Position des bounding rect</param>
/// <param name="w">Breite Position des bounding rect</param>
/// <param name="h">Höhe</param>
/// <param name="player">Spielernummer</param>
/// <param name="parent">Standardparameter</param>
Chip::Chip(int x, int y, int w, int h, int player, QObject *parent)
    : QObject(parent), QGraphicsEllipseItem((qreal)x,(qreal)y,(qreal)w,(qreal)h)
{
    this->player = player;
}

/// <summary>
/// Liefert einen Zeiger auf eine MyAnimation Instanz zurück,
/// die dann ausgeführt werden kann
/// </summary>
/// <param name="end">Endposition der Animation</param>
/// <param name="duration">Dauer der Animation</param>
/// <param name="curve">Zur Beeinflussung des Animationsverhaltens</param>
MyAnimation* Chip::animate(QPointF end, int duration,  const QEasingCurve &curve)
{
    MyAnimation* animation = new MyAnimation(this, "pos");
    animation->setDuration(duration);
    animation->setEndValue(end);
    animation->setEasingCurve(curve);
    return animation;
}



/// <summary>
/// Liefert einen Zeiger auf eine QPointF Instanz,
/// die den Mittelpunkt des Objektes beschreibt.
/// </summary>
QPointF* Chip::getCenter()
{
    QPointF *c = new QPointF();
    c->setX(pos().x() + boundingRect().width()/2);
    c->setY(pos().y() + boundingRect().width()/2);
  //  qDebug() << c->y();

    return c;
}

/// <summary>
/// Liefert den Spieler zurück, der den Stein gelegt hat.
/// </summary>
int Chip::getPlayer()
{
    return player;
}

